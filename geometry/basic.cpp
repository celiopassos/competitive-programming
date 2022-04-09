#define x real
#define y imag

template <typename T>
T dot(std::complex<T> a, std::complex<T> b) {
  return (std::conj(a) * b).x();
}

template <typename T>
T cross(std::complex<T> a, std::complex<T> b) {
  return (std::conj(a) * b).y();
}

template <typename T>
bool cw(std::complex<T> a, std::complex<T> b, std::complex<T> c) {
  return cross(b - a, c - b) < 0;
}

template <typename T>
bool ccw(std::complex<T> a, std::complex<T> b, std::complex<T> c) {
  return cross(b - a, c - b) > 0;
}

template <typename T>
std::istream& operator>>(std::istream& in, std::complex<T>& p) {
  int x, y;  // <- warning
  in >> x >> y;
  p = std::complex<T>(x, y);
  return in;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, std::complex<T> p) {
  return out << p.x() << " " << p.y();
}
