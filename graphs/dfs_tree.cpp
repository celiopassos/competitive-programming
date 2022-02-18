struct dfs_tree_t {
  int N, M;
  std::vector<std::vector<std::pair<int, int>>> E;
  std::vector<State> st;
  std::vector<int> dp, back;
  std::vector<bool> cut, bridge;
  dfs_tree_t(int N, const std::vector<std::array<int, 2>>& edges) :
    N(N), M(edges.size()), st(N), E(N), dp(N), back(N), cut(N), bridge(M)
  {
    for (int j = 0; j < M; ++j) {
      auto [u, v] = edges[j];
      if (u == v) continue;
      E[u].emplace_back(v, j);
      E[v].emplace_back(u, j);
    }
    for (int u = 0; u < N; ++u) {
      if (st[u] == unvisited) {
        dfs(u, -1);
      }
    }
  }
  std::vector<std::vector<int>> biconnected, two_edge_connected;
  std::stack<int> edge_stack, vertex_stack;
  void dfs(int u, int p) {
    st[u] = active;
    vertex_stack.push(u);
    int deg = 0;
    for (auto [v, j] : E[u]) {
      if (j == p) continue;
      if (st[v] == unvisited) {
        ++deg;
        edge_stack.push(j);
        dfs(v, j);
        int x = dp[v] - back[u];
        back[u] = 0;
        dp[u] += x;
        if (x == 0) {
          if (p != -1) {
            cut[u] = true;
          }
          std::vector<int> C;
          while (true) {
            int k = edge_stack.top();
            edge_stack.pop();
            C.push_back(k);
            if (k == j) break;
          }
          biconnected.push_back(std::move(C));
        }
        if (dp[v] == 0) {
          bridge[j] = true;
        }
      } else if (st[v] == active) {
        edge_stack.push(j);
        ++dp[u];
        ++back[v];
      }
    }
    st[u] = visited;
    if (dp[u] == 0) {
      std::vector<int> C;
      while (true) {
        int v = vertex_stack.top();
        vertex_stack.pop();
        C.push_back(v);
        if (v == u) break;
      }
      two_edge_connected.push_back(std::move(C));
    }
    if (deg > 1 && p == -1) {
      cut[u] = true;
    }
  }
};
