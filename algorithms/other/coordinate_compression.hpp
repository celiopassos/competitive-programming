#ifndef ALGORITHMS_OTHER_COORDINATE_COMPRESSION_HPP
#define ALGORITHMS_OTHER_COORDINATE_COMPRESSION_HPP

template <typename T>
struct CoordinateCompression : public std::vector<T> {
  template <typename... Args>
  CoordinateCompression(Args&&... args) : std::vector<T>(std::forward<Args>(args)...) {
    std::sort(this->begin(), this->end());
    this->erase(std::unique(this->begin(), this->end()), this->end());
  }
  int id(const T& value) const {
    return std::lower_bound(this->begin(), this->end(), value) - this->begin();
  }
};

#endif  // ALGORITHMS_OTHER_COORDINATE_COMPRESSION_HPP
