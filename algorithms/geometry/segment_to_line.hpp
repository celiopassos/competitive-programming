#ifndef ALGORITHMS_GEOMETRY_SEGMENT_TO_LINE_HPP
#define ALGORITHMS_GEOMETRY_SEGMENT_TO_LINE_HPP

#include "algorithms/geometry/line"

#include <complex>

template <typename T>
Line<T> line(Segment<T> S) {
  auto d = (S[1] - S[0]) * std::complex<T>(0, 1);
  return {d, dot(d, S[0])};
}

#endif  // ALGORITHMS_GEOMETRY_SEGMENT_TO_LINE_HPP
