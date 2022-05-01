#ifndef ALGORITHMS_GRAPHS_HLD_HPP
#define ALGORITHMS_GRAPHS_HLD_HPP

#include <utility>
#include <vector>

struct HLD {
  int N;
  std::vector<std::vector<int>> E;
  std::vector<int> p, h, head, L, R;

  HLD(const std::vector<std::vector<int>>& E, int root) : N(E.size()), E(E), p(N, -1), h(N), head(N), L(N), R(N) {
    dfs_sz(root);
    head[root] = root;
    dfs_hld(root);
  }

  int dfs_sz(int u) {
    int sz = 1, mx = 0;
    for (auto& v : E[u]) {
      if (v == p[u]) continue;
      p[v] = u, h[v] = h[u] + 1;
      int x = dfs_sz(v);
      sz += x;
      if (x > mx) {
        mx = x;
        std::swap(v, E[u][0]);
      }
    }
    return sz;
  }

  int timer = 0;
  void dfs_hld(int u) {
    L[u] = timer++;
    for (auto v : E[u]) {
      if (v == p[u]) continue;
      head[v] = (v == E[u][0] ? head[u] : v);
      dfs_hld(v);
    }
    R[u] = timer;
  }

  // Boolean is true if path should be 'reversed' (for uncommutative operations).
  const std::vector<std::tuple<bool, int, int>>& get_path(int u, int v) const {
    static std::vector<std::tuple<bool, int, int>> left, right;
    left.clear(), right.clear();
    while (head[u] != head[v]) {
      if (h[head[u]] > h[head[v]]) {
        left.emplace_back(true, L[head[u]], L[u] + 1);
        u = p[head[u]];
      } else {
        right.emplace_back(false, L[head[v]], L[v] + 1);
        v = p[head[v]];
      }
    }
    if (h[u] > h[v]) {
      left.emplace_back(true, L[v], L[u] + 1);
    } else {
      right.emplace_back(false, L[u], L[v] + 1);
    }
    left.insert(left.end(), right.rbegin(), right.rend());
    return left;
  }

  int lca(int u, int v) const {
    while (head[u] != head[v]) {
      if (h[head[u]] < h[head[v]]) std::swap(u, v);
      u = p[head[u]];
    }
    return h[u] < h[v] ? u : v;
  }
};

#endif  // ALGORITHMS_GRAPHS_HLD_HPP
