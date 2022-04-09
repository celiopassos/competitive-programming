#ifndef ALGORITHMS_GRAPHS_VIRTUAL_TREE_HPP
#define ALGORITHMS_GRAPHS_VIRTUAL_TREE_HPP

#include "algorithms/common"

#include <stack>

// Builds virtual tree on F given the vertex set V and returns its root.
// V is modified to contain the new vertices and is sorted by lca.L[u].
template <typename LCA>
int build_virtual_tree(std::vector<int>& V, std::vector<std::vector<int>>& F, const LCA& lca) {
  auto cmp = [&](int u, int v) { return lca.L[u] > lca.L[v]; };
  std::sort(V.begin(), V.end(), cmp);
  int k = V.size();
  for (int j = 0; j + 1 < k; ++j) {
    V.push_back(lca.lca(V[j], V[j + 1]));
  }
  std::sort(V.begin(), V.end(), cmp);
  V.erase(std::unique(V.begin(), V.end()), V.end());
  std::stack<int> stk;
  for (auto u : V) {
    while (!stk.empty() && lca.is_ancestor(u, stk.top())) {
      F[u].push_back(stk.top());
      stk.pop();
    }
    stk.push(u);
  }
  return stk.top();
}

#endif  // ALGORITHMS_GRAPHS_VIRTUAL_TREE_HPP
