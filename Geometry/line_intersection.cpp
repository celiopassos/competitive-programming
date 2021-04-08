// finds point x with dot(L.first, x) = L.second and dot(K.first, x) = K.second
// assumes that L and K are not parallel (division by 0 otherwise)
template<typename T>
complex<T> intersection(pair<complex<T>, T> L, pair<complex<T>, T> K) {
    auto [a, t] = L;
    auto [b, s] = K;
    T div = cross(a, b);
    T x = cross(complex(t, s), complex<T>(a.y(), b.y())) / div;
    T y = -cross(complex(t, s), complex<T>(a.x(), b.x())) / div;
    return complex(x, y);
}
