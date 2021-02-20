#define x real
#define y imag

template<typename T>
T dot(complex<T> a, complex<T> b) { return (conj(a) * b).x(); }

template<typename T>
T cross(complex<T> a, complex<T> b) { return (conj(a) * b).y(); }

template<typename T>
bool cw(complex<T> a, complex<T> b, complex<T> c)
{
    return cross(b - a, c - b) < 0;
}

template<typename T>
bool ccw(complex<T> a, complex<T> b, complex<T> c)
{
    return cross(b - a, c - b) > 0;
}

template<typename T>
int up(complex<T> a)
{
    if (a.x() == 0 && a.y() == 0) return 0;
    return a.y() > 0 || a.y() == 0 && a.x() < 0 ? +1 : -1;
}

// sorts by atan2
template<typename T>
bool arg_cmp(complex<T> a, complex<T> b)
{
    return up(a) == up(b) ? cross(a, b) > 0 : up(a) < up(b);
}

template<typename T>
bool lex_cmp(complex<T> a, complex<T> b)
{
    return a.x() != b.x() ? a.x() < b.x() : a.y() < b.y();
}

template<typename T>
istream& operator>>(istream& in, complex<T>& p)
{
    T x, y;
    in >> x >> y;
    p.x(x), p.y(y);
    return in;
}
