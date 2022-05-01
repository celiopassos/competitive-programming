#ifndef ALGORITHMS_MATHEMATICS_FFT_HPP
#define ALGORITHMS_MATHEMATICS_FFT_HPP

#include <cassert>
#include <utility>
#include <vector>

template <typename T>
struct RootOfUnity;  // Not implemented for general T.

template <typename T>
class FFT {
public:
  static constexpr int maxN = 1 << 20;

  static std::vector<T> dft(std::vector<T> p) {
    return get_instance().transform(std::move(p), false);
  }
  static std::vector<T> idft(std::vector<T> p) {
    return get_instance().transform(std::move(p), true);
  }

private:
  static const FFT& get_instance() {
    static FFT fft(maxN);
    return fft;
  }

  std::vector<int> revs;
  std::vector<T> roots;

  FFT(int N) : roots(2 * (N - 1)), revs(2 * N) {
    if (N == 1) return;
    int* rev = revs.data();
    for (int b = 1; b < N; b <<= 1) {
      int* nrev = rev + b;
      for (int i = 0; i < b; ++i) {
        nrev[i] = rev[i] << 1;
        nrev[i | b] = nrev[i] | 1;
      }
      rev = nrev;
    }
    T* root = roots.data();
    for (int sgn : {+1, -1}) {
      root[0] = 1;
      for (int b = 2; b < N; b <<= 1) {
        T w = RootOfUnity<T>::root_of_unity(sgn * 2 * b);
        T* nroot = root + (b >> 1);
        for (int i = 0; i < b; ++i) {
          nroot[i] = root[i >> 1];
          if (i & 1) {
            nroot[i] *= w;
          }
        }
        root = nroot;
      }
      root += N >> 1;
    }
  }

  std::vector<T> transform(std::vector<T> p, bool inverse) const {
    int N = p.size();
    assert((N & (N - 1)) == 0 && N <= maxN);
    const int* rev = revs.data() + N - 1;
    for (int i = 0; i < N; ++i) {
      if (i < rev[i]) {
        std::swap(p[i], p[rev[i]]);
      }
    }
    const T* root = roots.data();
    if (inverse) {
      root += roots.size() / 2;
    }
    for (int b = 1; b < N; b <<= 1) {
      for (int s = 0; s < N; s += 2 * b) {
        for (int i = 0; i < b; ++i) {
          int u = s | i, v = u | b;
          T x = p[u], y = root[i] * p[v];
          p[u] = x + y;
          p[v] = x - y;
        }
      }
      root += b;
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
    p.resize(K);
    q.resize(K);
    auto phat = FFT<T>::dft(std::move(p));
    auto qhat = FFT<T>::dft(std::move(q));
    for (int i = 0; i < K; ++i) {
      phat[i] *= qhat[i];
    }
    auto res = FFT<T>::idft(std::move(phat));
    res.resize(R);
    return res;
  }
}

#endif  // ALGORITHMS_MATHEMATICS_FFT_HPP
