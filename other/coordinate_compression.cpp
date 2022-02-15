template <typename T>
struct CoordinateCompression {
  std::vector<T> a;
  template <typename Iterator>
  CoordinateCompression(Iterator first, Iterator last) : a(first, last) {
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
  }
  T operator[](int j) const {
    return a[j];
  }
  T& operator[](int j) {
    return a[j];
  }
  int id(T x) const {
    return std::lower_bound(a.begin(), a.end(), x) - a.begin();
  }
  int size() const {
    return a.size();
  }
};
