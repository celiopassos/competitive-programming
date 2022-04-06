template <typename T>
struct root_of_unity_t {};

template <typename T>
struct root_of_unity_t<std::complex<T>> {
  static constexpr T PI = std::acos(-1);
  static std::complex<T> root_of_unity(int N) {
    return std::polar<T>(1, 2 * PI / N);
  }
};

constexpr int ntt_mod = 998244353;
template <>
struct root_of_unity_t<Z<ntt_mod>> {
  static constexpr Z<ntt_mod> g = Z<ntt_mod>(3);
  static Z<ntt_mod> root_of_unity(int N) {
    return pow(g, int(ntt_mod - 1) / N);
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
    for (auto sgn : {+1, -1}) {
      for (int b = 1; b < N; b <<= 1) {
        T w = root_of_unity_t<T>::root_of_unity(sgn * 2 * b);
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

constexpr int naive_threshold = 64;

template <typename T>
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  int N = p.size(), M = q.size();
  if (N == 0 || M == 0) {
    return {};
  } else if (std::min(N, M) <= naive_threshold) {
    std::vector<T> res(N + M - 1);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        res[i + j] += p[i] * q[j];
      }
    }
    return res;
  } else {
    int R = N + M - 1, K = 1;
    while (K < R) K <<= 1;
    fft_t<T> fft(K);
    auto phat = fft(std::move(p), false), qhat = fft(std::move(q), false);
    for (int i = 0; i < K; ++i) {
      phat[i] *= qhat[i];
    }
    auto res = fft(std::move(phat), true);
    res.resize(R);
    return res;
  }
}
