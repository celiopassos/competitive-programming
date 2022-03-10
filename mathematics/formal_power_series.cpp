template <typename T>
T root_of_unity(int N);

template <>
std::complex<double> root_of_unity<std::complex<double>>(int N) {
  static constexpr double PI = std::acos(-1);
  return std::polar<double>(1, 2 * PI / N);
}

constexpr int ntt_mod = 998244353;
template <>
Z<ntt_mod> root_of_unity(int N) {
  return Z<ntt_mod>(3).power((ntt_mod - 1) / N);
}

template <typename T>
struct fft_t {
  int N;
  std::vector<int> rev;
  std::vector<T> q, r;
  fft_t(int N) : N(N), rev(N), q(N), r(N) {
    for (int i = 0; i < N; ++i) {
      int r = 0;
      for (int b = 1, j = i; b < N; b <<= 1, j >>= 1) {
        r = (r << 1) | j & 1;
      }
      rev[i] = r;
    }
  }
  std::vector<T> operator()(std::vector<T> p, bool inverse) {
    p.resize(N);
    for (int i = 0; i < N; ++i) {
      q[rev[i]] = p[i];
    }
    std::swap(p, q);
    for (int b = 1; b < N; b <<= 1) {
      r[0] = 1;
      r[1] = root_of_unity<T>((inverse ? -1 : +1) * 2 * b);
      for (int i = 1; i + 1 < 2 * b; ++i) {
        r[i + 1] = r[i] * r[1];
      }
      int prefix = 2 * b - 1;
      for (int i = 0; i < N; ++i) {
        q[i] = p[i & ~b] + r[i & prefix] * p[i | b];
      }
      std::swap(p, q);
    }
    if (inverse) {
      T inv = T(1) / T(N);
      for (int i = 0; i < N; ++i) p[i] *= inv;
    }
    return p;
  }
};

template <typename T>
struct FormalPowerSeries : public std::vector<T> {
  using F = FormalPowerSeries;
  using std::vector<T>::vector;
  FormalPowerSeries() : std::vector<T>(1) {}

  F operator+(const F& rhs) const {
    return F(*this) += rhs;
  }
  F& operator+=(const F& rhs) const {
    if (this->size() < rhs.size()) {
      this->resize(rhs.size());
    }
    for (int i = 0; i < rhs.size(); ++i) {
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  F operator-(const F& rhs) const {
    return F(*this) -= rhs;
  }
  F& operator-=(const F& rhs) const {
    if (this->size() < rhs.size()) {
      this->resize(rhs.size());
    }
    for (int i = 0; i < rhs.size(); ++i) {
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  F naive_multiply(const F& rhs) const {
    int N = this->size(), M = rhs.size();
    F r(N + M - 1);
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
        r[i + j] += (*this)[i] * rhs[j];
      }
    }
    return r;
  }
  F operator*(const F& rhs) {
    return F(*this) *= rhs;
  }
  F& operator*=(const F& rhs) {
    if (std::min(this->size(), rhs.size()) <= 64) {
      auto r = naive_multiply(rhs);
      this->swap(r);
    } else {
      int N = this->size() + rhs.size() - 1, M = 1;
      while (M < N) M <<= 1;
      fft_t<T> fft(M);
      auto phat = fft(std::move(*this), false), qhat = fft(rhs, false);
      for (int i = 0; i < M; ++i) {
        phat[i] *= qhat[i];
      }
      auto r = fft(phat, true);
      this->swap(r);
      this->resize(N);
    }
    return *this;
  }

  template <typename Solver>
  void solve(int l, int r, F& A, Solver&& solver) const {
    if (r - l == 1) {
      solver(A, l);
    } else {
      int len = r - l, m = (l + r) / 2;
      solve(l, m, A, solver);
      F a(A.begin() + l, A.begin() + m);
      const F& B = *this;
      F b(B.begin(), B.begin() + std::min<int>(B.size(), len));
      a *= b;
      for (int i = m - l; i < r - l && i < a.size(); ++i) {
        A[i + l] += a[i];
      }
      solve(m, r, A, solver);
    }
  }
  template <typename Solver>
  F solve(Solver&& solver) const {
    int N = this->size();
    F A(N);
    solve(0, N, A, solver);
    return A;
  }
};

template <typename T>
FormalPowerSeries<T> inv(const FormalPowerSeries<T>& P) {
  assert(P[0] != 0);
  auto solver = [mult = 1 / P[0]](auto& A, int i) {
    A[i] = (i == 0 ? 1 : -A[i]) * mult;
  };
  return P.solve(solver);
}

template <typename T>
FormalPowerSeries<T> D(FormalPowerSeries<T> P) {
  if (P.size() == 1) {
    P[0] = 0;
  } else {
    for (int i = 0; i + 1 < P.size(); ++i) {
      P[i] = (i + 1) * P[i + 1];
    }
    P.pop_back();
  }
  return P;
}

template <typename T>
FormalPowerSeries<T> I(FormalPowerSeries<T> P) {
  int N = P.size();
  P.push_back(0);
  for (int i = N - 1; i >= 0; --i) {
    P[i + 1] = P[i] / (i + 1);
  }
  P[0] = 0;
  return P;
}

template <typename T>
FormalPowerSeries<T> log(const FormalPowerSeries<T>& P) {
  assert(P[0] == 1);
  int N = P.size();
  auto r = D(P) * inv(P);
  r.resize(N - 1);
  return I(std::move(r));
}

template <typename T>
FormalPowerSeries<T> exp(FormalPowerSeries<T> P) {
  assert(P[0] == 0);
  for (int i = 0; i < P.size(); ++i) {
    P[i] *= i;
  }
  auto solver = [&](auto& A, int n) {
    A[n] = n == 0 ? 1 : A[n] / T(n);
  };
  return P.solve(solver);
}

template <typename T>
FormalPowerSeries<T> pow(const FormalPowerSeries<T>& P, int64_t k) {
  int N = P.size();
  int t = 0;
  while (t < N && P[t] == 0) ++t;
  if (t == N || (t > 0 && k >= (N + t - 1) / t)) {
    return FormalPowerSeries<T>(N, 0);
  }
  int max = N - k * t;
  FormalPowerSeries<T> Q(P.begin() + t, P.begin() + t + max);
  T alpha = Q[0];
  for (int i = 0; i < Q.size(); ++i) {
    Q[i] /= alpha;
  }
  assert(Q[0] == 1);
  Q = log(Q);
  for (auto& x : Q) {
    x *= k;
  }
  Q = exp(Q);
  for (auto& x : Q) {
    x *= alpha.power(k);
  }
  Q.insert(Q.begin(), k * t, 0);
  return Q;
}
