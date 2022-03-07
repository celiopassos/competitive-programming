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
  std::vector<T> q;
  fft_t(int N) : N(N), rev(N), q(N) {
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
      T w = root_of_unity<T>((inverse ? -1 : +1) * 2 * b);
      for (auto [i, x] = std::pair<int, T>(0, 1); i < N; ++i, x *= w) {
        q[i] = p[i & ~b] + x * p[i | b];
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
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  int N = p.size() + q.size() - 1, M = 1;
  while (M < N) M <<= 1;
  fft_t<T> fft(M);
  auto phat = fft(p, false), qhat = fft(q, false);
  for (int i = 0; i < M; ++i) {
    phat[i] *= qhat[i];
  }
  auto r = fft(phat, true);
  r.resize(N);
  return r;
}
