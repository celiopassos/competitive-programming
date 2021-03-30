// finds point x with dot(a, x) = t and dot(b, x) = s
template<typename T>
complex<T> intersection(complex<T> a, T t, complex<T> b, T s) {
    T div = cross(a, b);
    T x = cross(complex(t, s), complex<T>(a.y(), b.y())) / div;
    T y = -cross(complex(t, s), complex<T>(a.x(), b.x())) / div;
    return complex(x, y);
}
