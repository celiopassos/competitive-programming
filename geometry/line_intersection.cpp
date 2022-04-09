// Finds point x with dot(L.first, x) = L.second and dot(K.first, x) = K.second.
// Assumes that L and K are not parallel (division by 0 otherwise)
template <typename T, typename F = double>
std::complex<F> intersection(Line<T> L, Line<T> K) {
  auto [a, t] = L;
  auto [b, s] = K;
  F div = (F)cross(a, b);
  F x = (F)cross(std::complex(t, s), std::complex(a.y(), b.y())) / div;
  F y = -(F)cross(std::complex(t, s), std::complex(a.x(), b.x())) / div;
  return std::complex<F>(x, y);
}
