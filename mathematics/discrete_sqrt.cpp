namespace flags {
bool zp_sqrt_failed;
};

template <unsigned int P>
Z<P> sqrt(Z<P> alpha) {
  if (pow(alpha, (P - 1) / 2) != 1) {
    flags::zp_sqrt_failed = true;
    return Z<P>();
  } else {
    flags::zp_sqrt_failed = false;
  }
  static Z<P> alpha_;
  alpha_ = alpha;
  struct R {
    Z<P> a, b;
    R operator*(const R& rhs) const {
      return R{a * rhs.a + alpha_ * b * rhs.b, a * rhs.b + b * rhs.a};
    }
  };
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<unsigned int> unif(0, P - 1);
  while (true) {
    Z<P> y = unif(rng);
    if (y * y == alpha) {
      return y;
    }
    auto x = R{y, 1};
    R pow{1, 0};
    for (int p = (P - 1) / 2; p; p >>= 1) {
      if (p & 1) {
        pow = pow * x;
      }
      x = x * x;
    }
    if (pow.b != 0) {
      return 1 / pow.b;
    }
  }
}
