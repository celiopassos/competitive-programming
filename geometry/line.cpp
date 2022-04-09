template <typename T>
using Line = std::pair<std::complex<T>, T>;  // Represents hyperplane dot(first, x) = second.

template <typename T>
using Segment = std::array<std::complex<T>, 2>;
