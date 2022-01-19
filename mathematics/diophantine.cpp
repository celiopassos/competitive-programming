template <typename T>
bool diophantine(T a, T b, T c, T& x, T& y) {
  T g = extended_gcd<T>(llabs(a), llabs(b), x, y);
  if (c % g) return false;
  x *= c / g;
  y *= c / g;
  if (a < 0) x *= -1;
  if (b < 0) y *= -1;
  return true;
}
