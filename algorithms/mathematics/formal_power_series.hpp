#ifndef ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_HPP
#define ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_HPP

#include "algorithms/mathematics/combinatorics"
#include "algorithms/mathematics/convolution_base"

#include <algorithm>
#include <deque>
#include <utility>
#include <vector>

template <typename T>
struct FormalPowerSeries : public std::vector<T> {
  using F = FormalPowerSeries;

  using std::vector<T>::vector;
  template <typename... Args>
  explicit FormalPowerSeries(Args&&... args) : std::vector<T>(std::forward<Args>(args)...) {}

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

  F operator*(T alpha) const {
    return F(*this) *= alpha;
  }

  F& operator*=(T alpha) {
    for (auto& x : *this) {
      x *= alpha;
    }
    return *this;
  }

  friend F operator*(T alpha, F rhs) {
    return rhs *= alpha;
  }

  F operator/(T alpha) const {
    return F(*this) *= 1 / alpha;
  }

  F& operator/=(T alpha) {
    return *this *= 1 / alpha;
  }

  F operator-() const {
    return F() -= *this;
  }

  F operator*(F rhs) const {
    return F(::operator*<T>(*this, std::move(rhs)));
  }

  F& operator*=(F rhs) {
    return *this = F(::operator*<T>(std::move(*this), std::move(rhs)));
  }

  std::pair<F, F> naive_division(const F& d) const {
    assert(!d.empty() && d.back() != 0);
    F q, r = *this;
    while (r.size() >= d.size()) {
      T c = r.back() / d.back();
      q.push_back(c);
      for (int i = 0; i < d.size(); ++i) {
        r.rbegin()[i] -= c * d.rbegin()[i];
      }
      r.pop_back();
    }
    if (q.empty()) {
      q.push_back(0);
    }
    if (r.empty()) {
      r.push_back(0);
    }
    std::reverse(q.begin(), q.end());
    return std::pair<F, F>(std::move(q), std::move(r));
  }

  F operator/(F d) const {
    assert(!d.empty() && d.back() != 0);
    int N = this->size(), M = d.size();
    if (N < M) {
      return {};
    } else if (M <= 64) {
      return naive_division(d).first;
    } else {
      int K = N - M + 1;
      std::reverse(d.begin(), d.end());
      d.resize(K);
      auto res = F(this->rbegin(), this->rbegin() + K) * inv(d);
      res.resize(K);
      std::reverse(res.begin(), res.end());
      return res;
    }
  }

  F& operator/=(const F& rhs) {
    return *this = *this / rhs;
  }

  F operator%(const F& rhs) const {
    return euclidean_division(rhs).second;
  }

  F operator%=(const F& rhs) {
    return *this = euclidean_division(rhs)->second;
  }

  std::pair<F, F> euclidean_division(const F& d) const {
    assert(!d.empty() && d.back() != 0);
    if (d.size() <= 64) {
      return naive_division(d);
    } else {
      auto q = *this / d;
      F q0(q.begin(), q.begin() + std::min(q.size(), d.size()));
      auto r = *this - d * q0;
      r.resize(d.size() - 1);
      return std::pair<F, F>(std::move(q), std::move(r));
    }
  }

  T operator()(T x) const {
    T pow = 1, y = 0;
    for (auto c : *this) {
      y += c * pow;
      pow *= x;
    }
    return y;
  }

  void trim_left() {
    this->erase(this->begin(), this->begin() + val(*this));
  }

  void trim_right() {
    while (!this->empty() && this->back() == 0) {
      this->pop_back();
    }
  }
};

template <typename T>
int deg(const FormalPowerSeries<T>& P) {
  auto iter = std::find_if(P.rbegin(), P.rend(), [](T c) { return c != 0; });
  return int(P.size() - (iter - P.rbegin())) - 1;
}

template <typename T>
int val(const FormalPowerSeries<T>& P) {
  auto iter = std::find_if(P.begin(), P.end(), [](T c) { return c != 0; });
  return iter - P.begin();
}

template <typename T>
FormalPowerSeries<T> product(const FormalPowerSeries<T>* p, int N) {
  if (N == 0) {
    return {1};
  } else if (N == 1) {
    return *p;
  } else {
    int h = N / 2;
    return product(p, h) * product(p + h, N - h);
  }
}


#include <iostream>

template <typename T>
FormalPowerSeries<T> inv(const FormalPowerSeries<T>& A) {
  int N = A.size();
  if (N == 1) {
    return {1 / A[0]};
  }
  auto Aneg = A;
  for (int i = 1; i < N; i += 2) {
    Aneg[i] = -A[i];
  }
  auto B = A * Aneg;
  int K = (N + 1) / 2;
  FormalPowerSeries<T> C(K);
  for (int i = 0; i < K; ++i) {
    C[i] = B[2 * i];
  }
  auto invC = inv(C);
  FormalPowerSeries<T> invB(N);
  for (int i = 0; i < K; ++i) {
    invB[2 * i] = invC[i];
  }
  auto res = Aneg * invB;
  res.resize(N);
  return res;
}

template <typename T>
FormalPowerSeries<T> D(FormalPowerSeries<T> P) {
  if (P.empty()) {
    return P;
  }
  for (int i = 0; i + 1 < P.size(); ++i) {
    P[i] = (i + 1) * P[i + 1];
  }
  P.pop_back();
  return P;
}

template <typename T>
FormalPowerSeries<T> I(FormalPowerSeries<T> P) {
  int N = P.size();
  P.push_back(0);
  for (int i = N - 1; i >= 0; --i) {
    P[i + 1] = P[i] * Combinatorics<T>::r(i + 1);
  }
  P[0] = 0;
  return P;
}

template <typename T>
FormalPowerSeries<T> log(const FormalPowerSeries<T>& P) {
  assert(!P.empty() && P[0] == 1);
  int N = P.size();
  auto r = D(P) * inv(P);
  r.resize(N - 1);
  return I(std::move(r));
}

template <typename T>
FormalPowerSeries<T> exp(const FormalPowerSeries<T>& P) {
  assert(P.empty() || P[0] == 0);
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
FormalPowerSeries<T> pow(const FormalPowerSeries<T>& P, T alpha) {
  assert(!P.empty() && P[0] == 1);
  return exp(alpha * log(P));
}

// Returns composition f(g(x)) modulo x^M.
// Time complexity: O(N * M).
template <typename T>
FormalPowerSeries<T> composition(const FormalPowerSeries<T>& f, const FormalPowerSeries<T>& g) {
  using F = FormalPowerSeries<T>;
  int N = f.size(), M = g.size();
  int block_size = 1;
  while ((block_size + 1) * (block_size + 1) <= N) ++block_size;
  std::vector<F> pow(block_size);
  pow[0] = {1};
  for (int k = 0; k + 1 < block_size; ++k) {
    pow[k + 1] = pow[k] * g;
    pow[k + 1].resize(M);
  }
  F h = pow.back() * g;
  h.resize(M);
  F offset = {1}, res;
  for (int i = 0; i < N; i += block_size) {
    F p;
    for (int k = 0; k < block_size && i + k < N; ++k) {
      p += f[i + k] * pow[k];
    }
    p.resize(M);
    res += offset * p;
    offset *= h;
    offset.resize(M);
  }
  res.resize(M);
  return res;
}

namespace sparse {

template <typename T>
std::vector<int> non_zero(const FormalPowerSeries<T>& P) {
  std::vector<int> I;
  for (int i = 0; i < P.size(); ++i) {
    if (P[i] != 0) {
      I.push_back(i);
    }
  }
  return I;
}

// Time complexity of the operations below: O(N * non_zero(P).size()).

template <typename T>
FormalPowerSeries<T> inv(const FormalPowerSeries<T>& P) {
  assert(!P.empty() && P[0] != 0);
  int N = P.size();
  auto I = non_zero(P);
  I.erase(I.begin());
  FormalPowerSeries<T> Q(N);
  Q[0] = 1 / P[0];
  for (int j = 1; j < N; ++j) {
    for (auto i : I) {
      if (i > j) break;
      Q[j] -= P[i] * Q[j - i];
    }
    Q[j] *= Q[0];
  }
  return Q;
}


template <typename T>
FormalPowerSeries<T> exp(const FormalPowerSeries<T>& P) {
  assert(!P.empty() && P[0] == 0);
  int N = P.size();
  auto dP = D(P);
  auto I = non_zero(dP);
  FormalPowerSeries<T> dQ(N - 1), Q(N);
  Q[0] = 1;
  for (int i = 0; i + 1 < N; ++i) {
    for (auto j : I) {
      if (j > i) break;
      dQ[i] += Q[i - j] * dP[j];
    }
    Q[i + 1] = Combinatorics<T>::r(i + 1) * dQ[i];
  }
  return Q;
}

template <typename T>
FormalPowerSeries<T> log(const FormalPowerSeries<T>& P) {
  assert(!P.empty() && P[0] == 1);
  int N = P.size();
  auto dP = D(P);
  auto J = non_zero(P);
  J.erase(J.begin());
  FormalPowerSeries<T> dQ(N - 1);
  for (int i = 0; i < N - 1; ++i) {
    dQ[i] += dP[i];
    for (auto j : J) {
      if (j > i) break;
      dQ[i] -= dQ[i - j] * P[j];
    }
  }
  return I(dQ);
}

template <typename T>
FormalPowerSeries<T> pow(const FormalPowerSeries<T>& P, T alpha) {
  assert(!P.empty() && P[0] == 1);
  int N = P.size();
  auto I = non_zero(P);
  I.erase(I.begin());
  auto dP = D(P);
  FormalPowerSeries<T> Q(N), dQ(N - 1);
  Q[0] = 1;
  for (int i = 0; i + 1 < N; ++i) {
    for (auto j : I) {
      --j;
      if (j > i) break;
      dQ[i] += dP[j] * Q[i - j];
    }
    dQ[i] *= alpha;
    for (auto j : I) {
      if (j > i) break;
      dQ[i] -= P[j] * dQ[i - j];
    }
    Q[i + 1] = dQ[i] * Combinatorics<T>::r(i + 1);
  }
  return Q;
}

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

  // Range [first, last) should be the domain points.
  template <typename Iterator>
  Interpolator(Iterator first, Iterator last) {
    deq.emplace_back();
    Node* root = &deq.back();
    build(root, first, last);
  }

  template <typename Iterator>
  void build(Node* node, Iterator first, Iterator last) {
    int len = last - first;
    if (len == 1) {
      node->P = {-first[0], T(1)};
    } else {
      deq.emplace_back();
      node->left = &deq.back();
      deq.emplace_back();
      node->right = &deq.back();
      Iterator middle = first + len / 2;
      build(node->left, first, middle);
      build(node->right, middle, last);
      node->P = node->left->P * node->right->P;
    }
  }

  std::vector<T> res;

  // Evaluates Q in the domain points.
  std::vector<T> evaluate(const F& Q) {
    res.clear();
    evaluate_aux(&deq[0], Q % deq[0].P);
    return std::move(res);
  }

  void evaluate_aux(Node* node, const F& Q) {
    if (node->left) {
      for (auto next : {node->left, node->right}) {
        evaluate_aux(next, Q % next->P);
      }
    } else {
      assert(Q.size() == 1);
      res.push_back(Q[0]);
    }
  }

  bool initiliazed = false;

  // Range [first, last) should be the image.
  // Returns the unique polynomial P with evaluate(P) = [first, last).
  template <typename Iterator>
  F interpolate(Iterator first, Iterator last) {
    if (!initiliazed) {
      auto y = evaluate(D(deq[0].P));
      auto iter = y.begin();
      for (auto& node : deq) {
        if (node.left) continue;
        node.y = *iter;
        ++iter;
      }
      initiliazed = true;
    }
    return interpolate_aux(&deq[0], first, last);
  }

  template <typename Iterator>
  F interpolate_aux(Node* node, Iterator first, Iterator last) {
    int len = last - first;
    if (len == 1) {
      return {first[0] / node->y};
    } else {
      Iterator middle = first + len / 2;
      return node->right->P * interpolate_aux(node->left, first, middle) +
        node->left->P * interpolate_aux(node->right, middle, last);
    }
  }

  // Assumes the size of P is the same as the number of points.
  F to_newton_basis(F P) {
    return to_newton_basis_aux(&deq[0], P);
  }

  F to_newton_basis_aux(Node* node, const F& P) {
    if (node->left) {
      auto [Q, R] = P.euclidean_division(node->left->P);
      F A = to_newton_basis_aux(node->left, R);
      F B = to_newton_basis_aux(node->right, Q);
      B.insert(B.begin(), A.size(), 0);
      return A + B;
      return {};
    } else {
      assert(P.size() == 1);
      return {P[0]};
      return {};
    }
  }
};

// Returns a vector y of size M with y[i] = p(a r^i).
template <typename T>
std::vector<T> chirp_z_transform(FormalPowerSeries<T> p, T a, T r, int M) {
  if (r == 0) {
    std::vector<T> y(M);
    y[0] = p(a);
    if (1 < M) {
      y[1] = p[0];
      for (int j = 2; j < M; ++j) {
        y[j] = y[1];
      }
    }
    return y;
  }

  int N = p.size();

  FormalPowerSeries<T> A(N);
  for (int i = 0; i < N; ++i) {
    int idx = N - 1 - i;
    long long e = 1LL * i * (i - 1) / 2;
    A[idx] = p[i] * pow(a, i) / pow(r, e);
  }

  FormalPowerSeries<T> B(N + M);
  for (int i = 0; i < N + M; ++i) {
    long long e = 1LL * i * (i - 1) / 2;
    B[i] = pow(r, e);
  }

  auto C = A * B;

  std::vector<T> y(M);
  for (int i = 0; i < M; ++i) {
    long long e = 1LL * i * (i - 1) / 2;
    y[i] = C[i + N - 1] / pow(r, e);
  }

  return y;
}


namespace scaled {

// Returns exp(alpha * x) mod x^N.
template <typename T>
FormalPowerSeries<T> exp(T alpha, int N) {
  FormalPowerSeries<T> f(N);
  T pow = 1;
  for (int k = 0; k < N; ++k) {
    f[k] = pow * Combinatorics<T>::rf(k);
    pow *= alpha;
  }
  return f;
}


}  // scaled

// Maps x^k -> x^k / k!.
template <typename T>
FormalPowerSeries<T> borel(FormalPowerSeries<T> P) {
  const auto& combi = Combinatorics<T>::get_instance();
  std::transform(P.begin(), P.end(), std::begin(combi.rfact), P.begin(), std::multiplies<T>());
  return P;
}

// Maps x^k -> k! * x^k.
template <typename T>
FormalPowerSeries<T> laplace(FormalPowerSeries<T> P) {
  const auto& combi = Combinatorics<T>::get_instance();
  std::transform(P.begin(), P.end(), std::begin(combi.fact), P.begin(), std::multiplies<T>());
  return P;
}

// Returns f(D)p.
template <typename T>
FormalPowerSeries<T> apply_power_series_of_derivative(FormalPowerSeries<T> f, FormalPowerSeries<T> p) {
  int N = p.size();
  if (f.size() > N) {
    f.resize(N);
  }
  std::reverse(f.begin(), f.end());
  auto res = f * laplace(std::move(p));
  res.erase(res.begin(), res.begin() + f.size() - 1);
  return borel(std::move(res));
}

// Returns the polynomial that sends x -> P(x + c).
template <typename T>
FormalPowerSeries<T> taylor_shift(FormalPowerSeries<T> P, T c) {
  int N = P.size();
  return apply_power_series_of_derivative(scaled::exp(c, N), std::move(P));
}

// FormalPowerSeries here are assumed to be given in the basis of falling factorials.
namespace falling_factorials {

template <typename T>
FormalPowerSeries<T> taylor_shift(FormalPowerSeries<T> P, T c) {
  int N = P.size();
  FormalPowerSeries<T> f(std::max(2, N));
  f[0] = f[1] = 1;
  return apply_power_series_of_derivative(sparse::pow<T>(std::move(f), c), std::move(P));
}

// Returns the unique polynomial P of degree < N with P(i) = y[i].
template <typename T>
FormalPowerSeries<T> interpolate(FormalPowerSeries<T> y) {
  int N = y.size();
  auto P = scaled::exp(T(-1), N) * borel(std::move(y));
  P.resize(N);
  return P;
}

// Inverse of the above transformation.
template <typename T>
FormalPowerSeries<T> evaluate(FormalPowerSeries<T> P) {
  int N = P.size();
  auto y = scaled::exp(T(1), N) * std::move(P);
  y.resize(N);
  return laplace(std::move(y));
}

// Evaluates at a single point x.
template <typename T>
T evaluate(FormalPowerSeries<T> P, T x) {
  T res = 0, fact = 1;
  for (int i = 0; i < P.size(); ++i) {
    res += P[i] * fact;
    fact *= x - i;
  }
  return res;
}

}  // namespace falling_factorials

// Returns P(c + j) for j = 0, ..., M - 1, where P is the unique polynomial of degree < N with P(i) = y[i].
template <typename T>
FormalPowerSeries<T> shift_of_sampling_points(FormalPowerSeries<T> y, T c, int M) {
  int N = y.size();
  auto P = falling_factorials::interpolate(std::move(y));
  P = falling_factorials::taylor_shift(std::move(P), c);
  P.resize(M);
  return falling_factorials::evaluate(std::move(P));
}

#endif  // ALGORITHMS_MATHEMATICS_FORMAL_POWER_SERIES_HPP
