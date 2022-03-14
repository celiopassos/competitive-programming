template <typename T>
struct root_of_unity {
  T operator()(int N) const = delete; // not implemented
};

template <typename T>
struct root_of_unity<std::complex<T>> {
  inline static constexpr T PI = std::acos(-1);
  std::complex<T> operator()(int N) const {
    return std::polar<T>(1, 2 * PI / N);
  }
};

template <uint32_t P>
int find_primitive_root() {
  constexpr int phi = P - 1;
  std::vector<int> primes;
  int x = phi;
  for (int p = 2; p * p <= x; ++p) {
    if (x % p) continue;
    primes.push_back(x);
    while (x % p == 0) x /= p;
  }
  if (x > 1) {
    primes.push_back(x);
  }
  for (int g = 1; g < P; ++g) {
    bool good = true;
    for (auto p : primes) {
      if (Z<P>(g).power(phi / p) == 1) {
        good = false;
        break;
      }
    }
    if (good) {
      return g;
    }
  }
  assert(false);
  return -1;
}

template <uint32_t P>
struct root_of_unity<Z<P>> {
  inline static const Z<P> g = P == 998244353 ? 3 : find_primitive_root<P>();
  Z<P> operator()(int N) const {
    return g.power(int(P - 1) / N);
  }
};

template <typename T>
struct fft_t {
  int N;
  std::vector<int> rev;
  std::vector<T> rs;
  fft_t(int N) : N(N), rev(N) {
    for (int i = 0; i < N; ++i) {
      int r = 0;
      for (int b = 1, j = i; b < N; b <<= 1, j >>= 1) {
        r = (r << 1) | j & 1;
      }
      rev[i] = r;
    }
    root_of_unity<T> rou;
    for (auto sgn : {+1, -1}) {
      for (int b = 1; b < N; b <<= 1) {
        T w = rou(sgn * 2 * b);
        rs.push_back(1);
        for (int i = 0; i + 1 < b; ++i) {
          rs.push_back(rs.back() * w);
        }
      }
    }
  }
  std::vector<T> operator()(std::vector<T> p, bool inverse) {
    p.resize(N);
    for (int i = 0; i < N; ++i) {
      if (i < rev[i]) {
        std::swap(p[i], p[rev[i]]);
      }
    }
    T* r = rs.data();
    if (inverse) {
      r += rs.size() / 2;
    }
    for (int b = 1; b < N; b <<= 1) {
      for (int s = 0; s < N; s += 2 * b) {
        for (int i = 0; i < b; ++i) {
          int u = s | i, v = u | b;
          T x = p[u], y = r[i] * p[v];
          p[u] = x + y;
          p[v] = x - y;
        }
      }
      r += b;
    }
    if (inverse) {
      T inv = T(1) / T(N);
      for (int i = 0; i < N; ++i) p[i] *= inv;
    }
    return p;
  }
};

template <typename T>
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  int N = p.size(), M = q.size();
  std::vector<T> res;
  if (std::min(N, M) <= 64) {
    res.resize(N + M - 1);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        res[i + j] += p[i] * q[j];
      }
    }
  } else {
    int R = N + M - 1, K = 1;
    while (K < R) K <<= 1;
    fft_t<T> fft(K);
    auto phat = fft(std::move(p), false), qhat = fft(std::move(q), false);
    for (int i = 0; i < K; ++i) {
      phat[i] *= qhat[i];
    }
    res = fft(std::move(phat), true);
    res.resize(N + M - 1);
  }
  return res;
}
