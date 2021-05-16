#define x real
#define y imag

template<typename T>
using Segment = array<complex<T>, 2>;

// represents points p with dot(Line.first, p) = Line.second
template<typename T>
using Line = pair<complex<T>, T>;

template<typename T>
T dot(complex<T> a, complex<T> b) { return (conj(a) * b).x(); }

template<typename T>
T cross(complex<T> a, complex<T> b) { return (conj(a) * b).y(); }

template<typename T>
bool cw(complex<T> a, complex<T> b, complex<T> c) { return cross(b - a, c - b) < 0; }

template<typename T>
bool ccw(complex<T> a, complex<T> b, complex<T> c) { return cross(b - a, c - b) > 0; }

template<typename T>
complex<T> normalized(complex<T> a) { return a / gcd<T>(a.x(), a.y()); }

template<typename T>
istream& operator>>(istream& in, complex<T>& p) {
    T x, y;
    in >> x >> y;
    p.x(x), p.y(y);
    return in;
}

template<typename T>
ostream& operator<<(ostream& out, complex<T> p) {
    return out << p.x() << " " << p.y();
}
