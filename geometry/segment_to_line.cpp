template <typename T>
Line<T> line(Segment<T> S) {
  auto d = (S[1] - S[0]) * std::complex<T>(0, 1);
  return {d, dot(d, S[0])};
}
