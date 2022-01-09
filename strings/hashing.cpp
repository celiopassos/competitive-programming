std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template <int K, int32_t P>
struct Hash {
  inline static const auto x = []() {
    std::array<int64_t, K> x;
    std::uniform_int_distribution<int64_t> unif(1, P - 1);
    for (int i = 0; i < K; ++i) {
      x[i] = unif(rng);
    }
    return x;
  }();
  inline static const auto xinv = []() {
    std::array<int64_t, K> xinv;
    for (int i = 0; i < K; ++i) {
      x[i] = unif(rng);
      xinv[i] = 1;
      for (int64_t p = P - 2, a = x[i]; p; p >>= 1) {
        if (p & 1) xinv[i] = xinv[i] * a % P;
        a = a * a % P;
      }
    }
    return xinv;
  }();
  std::array<int64_t, K> xp, xpinv, hash;
  Hash() {
    std::fill(xp.begin(), xp.end(), 1);
    std::fill(xpinv.begin(), xpinv.end(), 1);
    std::fill(hash.begin(), hash.end(), 0);
  }
  Hash(int64_t c) : xp(x), xpinv(xinv) {
    std::fill(hash.begin(), hash.end(), (c % P + P) % P);
  }
  Hash& operator+=(const Hash& rhs) {
    for (int i = 0; i < K; ++i) {
      xp[i] = xp[i] * rhs.xp[i] % P;
      xpinv[i] = xpinv[i] * rhs.xpinv[i] % P;
      hash[i] = (rhs.xp[i] * hash[i] + rhs.hash[i]) % P;
    }
    return *this;
  }
  Hash& operator-=(const Hash& rhs) {
    return *this += -rhs;
  }
  Hash operator+(const Hash& rhs) const {
    return Hash(*this) += rhs;
  }
  Hash operator-(const Hash& rhs) const {
    return Hash(*this) -= rhs;
  }
  Hash operator+() const {
    return *this;
  }
  Hash operator-() const {
    auto res = *this;
    for (int i = 0; i < K; ++i) {
      res.hash[i] = (P - xpinv[i]) * hash[i] % P;
      std::swap(res.xp[i], res.xpinv[i]);
    }
    return res;
  }
  Hash power(int64_t p) const {
    Hash h = *this;
    if (p < 0) p *= -1, h = -h;
    Hash res;
    while (p) {
      if (p & 1) res = res + h;
      h += h, p >>= 1;
    }
    return res;
  }
  bool operator==(const Hash& rhs) const {
    return hash == rhs.hash && xp == rhs.xp;
  }
  bool operator!=(const Hash& rhs) const {
    return !(*this == rhs);
  }
  struct custom_hash {
    inline static const size_t y =
        std::uniform_int_distribution<size_t>(1)(rng);
    size_t operator()(const Hash& h) const {
      size_t res = 0;
      for (int i = 0; i < K; ++i) {
        res = res * y + h.hash[i];
      }
      return res;
    }
  };
};
