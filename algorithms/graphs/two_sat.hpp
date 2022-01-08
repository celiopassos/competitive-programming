#ifndef ALGORITHMS_GRAPHS_TWO_SAT_HPP
#define ALGORITHMS_GRAPHS_TWO_SAT_HPP

#include "algorithms/graphs/tarjan"

#include <utility>
#include <vector>

struct TwoSat {
  int N;
  std::vector<std::vector<int>> E;
  TwoSat(int N) : N(N), E(2 * N) {}
  int neg(int u) const {
    return (u + N) % (2 * N);
  }
  void add_clause(int u, int v) {
    E[neg(u)].push_back(v);
    E[neg(v)].push_back(u);
  }

  // Assumes tarjan sorts SCCs in reverse topological order (u -> v implies scc[v] <= scc[u]).
  std::pair<bool, std::vector<bool>> solve() const {
    std::vector<bool> res(N);
    auto scc = tarjan(E);
    for (int u = 0; u < N; ++u) {
      if (scc[u] == scc[neg(u)]) return {false, {}};
      res[u] = scc[neg(u)] > scc[u];
    }
    return std::pair(true, res);
  }
};

#endif  // ALGORITHMS_GRAPHS_TWO_SAT_HPP
