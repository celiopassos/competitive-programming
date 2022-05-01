#ifndef ALGORITHMS_GEOMETRY_LINE_HPP
#define ALGORITHMS_GEOMETRY_LINE_HPP

#include <array>
#include <complex>
#include <utility>

template <typename T>
using Line = std::pair<std::complex<T>, T>;  // Represents hyperplane dot(first, x) = second.

template <typename T>
using Segment = std::array<std::complex<T>, 2>;

#endif  // ALGORITHMS_GEOMETRY_LINE_HPP
