template <typename T, int K>
struct Pointwise : public std::array<T, K> {
  using P = Pointwise;
  Pointwise(T value = 0) {
    std::fill(*this.begin(), *this.end(), value);
  }
  P& operator+=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] += rhs[j];
    return *this;
  }
  P& operator-=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] -= rhs[j];
    return *this;
  }
  P& operator*=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] *= rhs[j];
    return *this;
  }
  P& operator/=(const P& rhs) {
    for (int j = 0; j < K; ++j) (*this)[j] /= rhs[j];
    return *this;
  }
  friend P operator+(P lhs, const P& rhs) {
    return lhs += rhs;
  }
  friend P operator-(P lhs, const P& rhs) {
    return lhs -= rhs;
  }
  friend P operator*(P lhs, const P& rhs) {
    return lhs *= rhs;
  }
  friend P operator/(P lhs, const P& rhs) {
    return lhs /= rhs;
  }
  P operator+() const {
    return *this;
  }
  P operator-() const {
    return P(T(0)) -= *this;
  }
  P power(int64_t p) const {
    P res;
    for (int j = 0; j < K; ++j) res[j] = (*this)[j].power(p);
    return res;
  }
  inline static const Pointwise
      X =
          []() {
            std::uniform_int_distribution<int64_t> unif(
                1, std::numeric_limits<int64_t>::max());
            Pointwise X;
            std::mt19937 rng(
                std::chrono::steady_clock::now().time_since_epoch().count());
            for (int j = 0; j < K; ++j) X[j] = T(unif(rng));
            return X;
          }(),
      Xinv = P(1) / X;
  P& operator<<=(int64_t p) {
    return *this *= X.power(p);
  }
  P& operator>>=(int64_t p) {
    return *this *= Xinv.power(p);
  }
  P operator<<(int64_t p) const {
    return *this * X.power(p);
  }
  P operator>>(int64_t p) const {
    return *this * Xinv.power(p);
  }
};
