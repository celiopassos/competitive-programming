#ifndef ALGORITHMS_OTHER_CLAMP_HPP
#define ALGORITHMS_OTHER_CLAMP_HPP

template <typename T>
struct Clamp {
  static const T inf = std::numeric_limits<T>::max() / 2;

  T min, max, add;
  Clamp(T min = -inf, T max = +inf, T add = 0) : min(min), max(max), add(add) {}

  // Returns the composition: rhs is applied first, *this is applied after.
  Clamp operator*(Clamp rhs) const {
    T nadd = add + rhs.add;
    T nmin = std::clamp(rhs.min - rhs.add + nadd, min, max);
    T nmax = std::clamp(rhs.max - rhs.add + nadd, min, max);
    return Clamp(nmin, nmax, nadd);
  }

  T operator()(T x) const {
    return std::clamp(x + add, min, max);
  }
};

#endif  // ALGORITHMS_OTHER_CLAMP_HPP
