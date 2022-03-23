template <typename T>
struct FormalPowerSeries : public std::vector<T> {
  using F = FormalPowerSeries;
  using std::vector<T>::vector;
  FormalPowerSeries() : std::vector<T>(1) {}
  template <typename... Args>
  explicit FormalPowerSeries(Args&&... args) :
    std::vector<T>(std::forward<Args>(args)...) {}

  F operator+(const F& rhs) const {
    return F(*this) += rhs;
  }
  F& operator+=(const F& rhs) {
    if (this->size() < rhs.size()) {
      this->resize(rhs.size());
    }
    for (int i = 0; i < rhs.size(); ++i) {
      (*this)[i] += rhs[i];
    }
    return *this;
  }
  F operator-(const F& rhs) const {
    return F(*this) -= rhs;
  }
  F& operator-=(const F& rhs) {
    if (this->size() < rhs.size()) {
      this->resize(rhs.size());
    }
    for (int i = 0; i < rhs.size(); ++i) {
      (*this)[i] -= rhs[i];
    }
    return *this;
  }
  F& operator*=(T alpha) {
    for (auto& x : *this) {
      x *= alpha;
    }
    return *this;
  }
  F operator*(T alpha) const {
    return F(*this) *= alpha;
  }
  F operator/(T alpha) const {
    return F(*this) *= 1 / alpha;
  }
  friend F operator*(T alpha, F rhs) {
    return rhs *= alpha;
  }
  F operator-() const {
    return F() -= *this;
  }

  F operator*(const F& rhs) {
    return F(static_cast<std::vector<T>>(*this) * rhs);
  }
  F& operator*=(const F& rhs) {
    return *this = F(static_cast<std::vector<T>>(std::move(*this)) * rhs);
  }

  F operator/(const F& rhs) const {
    return F(*this) /= rhs;
  }
  F& operator/=(F rhs) {
    int N = this->size(), M = rhs.size();
    if (N < M) {
      *this = F();
    } else {
      int K = N - M + 1;
      std::reverse(rhs.begin(), rhs.end());
      rhs.resize(K);
      auto res = F(this->rbegin(), this->rbegin() + K) * inv(rhs);
      res.resize(K);
      std::reverse(res.begin(), res.end());
      this->swap(res);
    }
    return *this;
  }
  F operator%(const F& rhs) const {
    return divided_by(rhs).second;
  }
  F operator%=(const F& rhs) {
    return *this = divided_by(rhs)->second;
  }
  std::pair<F, F> divided_by(F rhs) const {
    auto q = *this / rhs;
    if (rhs.size() > 1) {
      rhs.pop_back();
    }
    auto q0 = F(q.begin(), q.begin() + std::min(q.size(), rhs.size()));
    auto r = *this - rhs * q0;
    r.resize(rhs.size());
    return {q, r};
  }

  T operator()(T x) const {
    T pow = 1, y = 0;
    for (auto& c : *this) {
      y += c * pow;
      pow *= x;
    }
    return y;
  }
};

template <typename T>
FormalPowerSeries<T> inv(const FormalPowerSeries<T>& P) {
  using F = FormalPowerSeries<T>;
  assert(P[0] != 0);
  F Q = {1 / P[0]};
  int N = P.size(), K = 1;
  while (K < N) {
    K *= 2;
    fft_t<T> fft(2 * K);
    auto Qhat = fft(Q, false);
    auto Phat = fft(F(P.begin(), P.begin() + std::min(K, N)), false);
    for (int i = 0; i < 2 * K; ++i) {
      Qhat[i] *= 2 - Phat[i] * Qhat[i];
    }
    auto nQ = fft(Qhat, true);
    Q.swap(nQ);
    Q.resize(K);
  }
  Q.resize(N);
  return Q;
}

template <typename T>
FormalPowerSeries<T> D(FormalPowerSeries<T> P) {
  if (P.size() == 1) {
    P[0] = 0;
  } else {
    for (int i = 0; i + 1 < P.size(); ++i) {
      P[i] = (i + 1) * P[i + 1];
    }
    P.pop_back();
  }
  return P;
}

template <typename T>
FormalPowerSeries<T> I(FormalPowerSeries<T> P) {
  int N = P.size();
  P.push_back(0);
  for (int i = N - 1; i >= 0; --i) {
    P[i + 1] = P[i] / (i + 1);
  }
  P[0] = 0;
  return P;
}

template <typename T>
FormalPowerSeries<T> log(const FormalPowerSeries<T>& P) {
  assert(P[0] == 1);
  int N = P.size();
  auto r = D(P) * inv(P);
  r.resize(N - 1);
  return I(std::move(r));
}

template <typename T>
FormalPowerSeries<T> exp(const FormalPowerSeries<T>& P) {
  assert(P[0] == 0);
  FormalPowerSeries<T> Q = {1};
  int N = P.size(), K = 1;
  while (K < N) {
    K *= 2;
    Q.resize(K);
    auto B = -log(Q);
    B[0] += 1;
    for (int i = 0; i < std::min(N, K); ++i) {
      B[i] += P[i];
    }
    Q *= B;
    Q.resize(K);
  }
  Q.resize(N);
  return Q;
}

template <typename T>
FormalPowerSeries<T> pow(FormalPowerSeries<T> P, int64_t k) {
  int N = P.size();
  int t = 0;
  while (t < N && P[t] == 0) ++t;
  if (t == N || (t > 0 && k >= (N + t - 1) / t)) {
    return FormalPowerSeries<T>(N, 0);
  }
  int max = N - k * t;
  P.erase(P.begin(), P.begin() + t);
  P.resize(max);
  T alpha = P[0];
  P *= 1 / alpha;
  P = pow(alpha, k) * exp(k * log(P));
  P.insert(P.begin(), k * t, 0);
  return P;
}

namespace flags {
  bool fps_sqrt_failed;
};

template <typename T>
FormalPowerSeries<T> sqrt(FormalPowerSeries<T> P) {
  int N = P.size();
  int t = 0;
  while (t < N && P[t] == 0) ++t;
  if (t == N) {
    return P;
  }
  auto x = sqrt(P[t]);
  if (t % 2 || x * x != P[t]) {
    flags::fps_sqrt_failed = true;
    return {};
  }
  P.erase(P.begin(), P.begin() + t);
  P.resize(N - t / 2);
  P *= 1 / P[0];
  P = x * exp(log(P) / 2);
  P.insert(P.begin(), t / 2, 0);
  flags::fps_sqrt_failed = false;
  return P;
}

template <typename T>
struct Interpolator {
  using F = FormalPowerSeries<T>;
  struct Node {
    F P;
    T y;
    Node* left = nullptr;
    Node* right = nullptr;
  };
  std::deque<Node> deq;
  template <typename Iterator>
  Interpolator(Iterator first, Iterator last) {
    Node* root = &deq.emplace_back();
    build(root, first, last);
  }
  template <typename Iterator>
  void build(Node* node, Iterator first, Iterator last) {
    int len = last - first;
    if (len == 1) {
      node->P = {-first[0], 1};
    } else {
      node->left = &deq.emplace_back();
      node->right = &deq.emplace_back();
      Iterator middle = first + len / 2;
      build(node->left, first, middle);
      build(node->right, middle, last);
      node->P = node->left->P * node->right->P;
    }
  }
  std::vector<T> res;
  std::vector<T> evaluate(const F& Q) {
    res.clear();
    evaluate(&deq[0], Q % deq[0].P);
    return std::move(res);
  }
  void evaluate(Node* node, F Q) {
    if (node->left) {
      for (auto next : {node->left, node->right}) {
        evaluate(next, Q % next->P);
      }
    } else {
      assert(Q.size() == 1);
      res.push_back(Q[0]);
    }
  }
  bool flag = false;
  template <typename Iterator>
  F interpolate(Iterator first, Iterator last) {
    if (!flag) {
      flag = true;
      auto y = evaluate(D(deq[0].P));
      auto iter = y.begin();
      for (auto& node : deq) {
        if (node.left) continue;
        node.y = *iter;
        ++iter;
      }
    }
    return interpolate(&deq[0], first, last);
  }
  template <typename Iterator>
  F interpolate(Node* node, Iterator first, Iterator last) {
    int len = last - first;
    if (len == 1) {
      return {first[0] / node->y};
    } else {
      Iterator middle = first + len / 2;
      return node->right->P * interpolate(node->left, first, middle) +
        node->left->P * interpolate(node->right, middle, last);
    }
  }
};

// computes P(D)A
template <typename T>
FormalPowerSeries<T> apply_polynomial_of_derivative(FormalPowerSeries<T> P,
    FormalPowerSeries<T> A) {
  int N = A.size();
  if (P.size() > N) {
    P.resize(N);
  }
  std::vector<T> f(N);
  f[0] = 1;
  for (int k = 0; k + 1 < N; ++k) {
    f[k + 1] = (k + 1) * f[k];
  }
  for (int k = 0; k < N; ++k) {
    A[k] *= f[k];
  }
  std::reverse(P.begin(), P.end());
  auto res = P * A;
  res.erase(res.begin(), res.begin() + P.size() - 1);
  for (int k = 0; k < N; ++k) {
    res[k] /= f[k];
  }
  return res;
}

// finds coefficients of polynomial x -> P(x + c)
template <typename T>
FormalPowerSeries<T> taylor_shift(FormalPowerSeries<T> P, T c) {
  int N = P.size();
  FormalPowerSeries<T> expc(N);
  T f = 1, pow = 1;
  for (int k = 0; k < N; ++k) {
    expc[k] = pow / f;
    f *= k + 1;
    pow *= c;
  }
  return apply_polynomial_of_derivative(expc, P);
}

// returns coefficients in the basis of falling factorials of the unique
// polynomial P (of degree < N) with P(i) = y[i] (the coefficient of y)
template <typename T>
FormalPowerSeries<T> interpolate_to_falling_factorials(FormalPowerSeries<T> y) {
  int N = y.size();
  FormalPowerSeries<T> exp(N);
  T f = 1;
  for (int k = 0; k < N; ++k) {
    exp[k] = (k % 2 ? -1 : +1) / f;
    y[k] /= f;
    f *= k + 1;
  }
  auto res = exp * y;
  res.resize(N);
  return res;
}
