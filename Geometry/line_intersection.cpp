// finds point x with dot(L.first, x) = L.second and dot(K.first, x) = K.second
// assumes that L and K are not parallel (division by 0 otherwise)
template<typename T, typename F = double>
complex<F> intersection(Line<T> L, Line<T> K) {
    auto [a, t] = L;
    auto [b, s] = K;
    F div = (F)cross(a, b);
    F x = (F)cross(complex(t, s), complex(a.y(), b.y())) / div;
    F y = -(F)cross(complex(t, s), complex(a.x(), b.x())) / div;
    return complex<F>(x, y);
}
