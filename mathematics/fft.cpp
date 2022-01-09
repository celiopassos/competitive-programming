template <typename T>
struct root_of_unity {
  T operator()(int N) const = delete;  // !implemented
};
template <typename T>
struct root_of_unity<std::complex<T>> {
  inline static const T PI = std::acos(-1);
  std::complex<T> operator()(int N) const {
    return std::polar<T>(1, 2 * PI / N);
  }
};
// constexpr int ntt_mod = 998244353;
// template<>
// struct root_of_unity<Z<ntt_mod>> {
//    Z<ntt_mod> operator()(int N) const {
//        return Z<ntt_mod>(3).power((ntt_mod - 1) / N);
//    }
// };
template <typename T>
std::vector<T> fft(std::vector<T> p, bool inverse) {
  int N = p.size();
  std::vector<T> q(N);
  for (int i = 0; i < N; ++i) {
    int rev = 0;
    for (int b = 1; b < N; b <<= 1) {
      rev = (rev << 1) | !!(i & b);
    }
    q[rev] = p[i];
  }
  std::swap(p, q);
  root_of_unity<T> rt;
  for (int b = 1; b < N; b <<= 1) {
    T w = rt(b << 1);
    if (inverse) w = T(1) / w;
    for (auto [i, x] = std::pair(0, T(1)); i < N; ++i, x *= w) {
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
template <typename T>
std::vector<T> operator*(std::vector<T> p, std::vector<T> q) {
  int N = p.size() + q.size() - 1, M = 1;
  while (M < N) M <<= 1;
  p.resize(M), q.resize(M);
  auto phat = fft(p, false), qhat = fft(q, false);
  for (int i = 0; i < M; ++i) {
    phat[i] *= qhat[i];
  }
  auto r = fft(phat, true);
  r.resize(N);
  return r;
}
