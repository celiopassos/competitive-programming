#ifndef ALGORITHMS_MATHEMATICS_FFT_HPP
#define ALGORITHMS_MATHEMATICS_FFT_HPP

#include <cassert>
#include <utility>
#include <vector>
#include <type_traits>

template <typename T>
struct RootOfUnity;  // Not implemented for general T.

template <typename T>
class FFT {
public:
  static constexpr int maxN = 1 << 22;

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


#endif  // ALGORITHMS_MATHEMATICS_FFT_HPP
