#ifndef ALGORITHMS_GRAPHS_MO_ON_TREES_HPP
#define ALGORITHMS_GRAPHS_MO_ON_TREES_HPP

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>

struct MoOnTree {
  int N, K;
  std::vector<int> block, p, L, R;

  int num_blocks = 0;
  void mark(std::vector<int>& S) {
    for (auto u : S) {
      block[u] = num_blocks;
    }
    ++num_blocks;
    S.clear();
  }

  int timer = 0;
  std::vector<int> decompose(int u, const std::vector<std::vector<int>>& E) {
    L[u] = timer++;
    std::vector<int> S;
    for (auto v : E[u]) {
      if (v == p[u]) continue;
      p[v] = u;
      auto R = decompose(v, E);
      S.insert(S.end(), R.begin(), R.end());
      if (S.size() > K) mark(S);
    }
    R[u] = timer;
    S.push_back(u);
    return S;
  }

  // Time complexity: O(N * K).
  MoOnTree(const std::vector<std::vector<int>>& E, int K) : N(E.size()), K(K), block(N), p(N, -1), L(N), R(N) {
    auto S = decompose(0, E);
    if (!S.empty()) mark(S);
  }

  bool is_ancestor(int u, int v) const {
    return L[u] <= L[v] && R[v] <= R[u];
  }

  template <typename Update>
  void traverse(std::array<int, 2> P, Update&& update) const {
    for (int t : {0, 1}) {
      while (!is_ancestor(P[t], P[t ^ 1])) {
        update(P[t]);
        P[t] = p[P[t]];
      }
    }
  }

  // Time complexity: O(N^2 / K + Q.size() * K).
  template <typename Evaluate, typename Update>
  void run(const std::vector<std::array<int, 2>>& Q, Evaluate&& evaluate, Update&& update) const {
    std::vector<int> Z(Q.size());
    std::iota(Z.begin(), Z.end(), 0);
    auto key = [&](int i) { return std::pair<int, int>(block[Q[i][0]], L[Q[i][1]]); };
    std::sort(Z.begin(), Z.end(), [&](int i, int j) { return key(i) < key(j); });
    std::array<int, 2> P = {0, 0};
    for (auto z : Z) {
      for (int t : {0, 1}) {
        traverse({P[t], Q[z][t]}, update);
        P[t] = Q[z][t];
      }
      evaluate(z);
    }
  }
};

#endif  // ALGORITHMS_GRAPHS_MO_ON_TREES_HPP
