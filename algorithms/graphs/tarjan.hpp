#ifndef ALGORITHMS_GRAPHS_TARJAN_HPP
#define ALGORITHMS_GRAPHS_TARJAN_HPP

#include <vector>
#include <stack>

// SCC ids are sorted in reverse order (i.e., an edge uv implies scc[v] <= scc[u]).
// It is guaranteed that 0 <= scc[u] < N for all u.
std::vector<int> tarjan(const std::vector<std::vector<int>>& E) {
  int N = E.size(), timer = 0, ct = 0;
  enum State { unvisited, active, visited };
  std::vector<State> state(N, unvisited);
  std::vector<int> low(N, -1), num(N, -1), scc(N, -1);
  std::stack<int> stk;
  auto dfs = [&](auto& self, int u) -> void {
    low[u] = num[u] = timer++, state[u] = active;
    stk.push(u);
    for (auto v : E[u]) {
      if (state[v] == unvisited) {
        self(self, v);
      }
      if (state[v] == active) {
        low[u] = std::min(low[u], low[v]);
      }
    }
    if (low[u] == num[u]) {
      do {
        int v = stk.top();
        stk.pop();
        scc[v] = ct;
        state[v] = visited;
      } while (!stk.empty() && num[stk.top()] >= num[u]);
      ++ct;
    }
  };
  for (int u = 0; u < N; ++u) {
    if (num[u] == -1) dfs(dfs, u);
  }
  return scc;
}

#endif  // ALGORITHMS_GRAPHS_TARJAN_HPP
