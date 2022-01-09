struct GraphicMatroid {
  int N, M;
  std::vector<std::array<int, 2>> edges;
  std::vector<std::vector<int>> E;
  std::vector<int> component, L, R;
  GraphicMatroid(int N, const std::vector<std::array<int, 2>>& edges_)
      : N(N), M(edges_.size()), edges(edges_), E(N), component(N), L(N), R(N) {}
  int timer = 0;
  void dfs(int u) {
    L[u] = timer++;
    for (auto v : E[u]) {
      if (L[v] != -1) continue;
      component[v] = component[u];
      dfs(v);
    }
    R[u] = timer;
  }
  void build(const std::vector<int>& I) {
    timer = 0;
    for (int u = 0; u < N; ++u) {
      E[u].clear();
      L[u] = -1;
    }
    for (auto e : I) {
      auto [u, v] = edges[e];
      E[u].push_back(v);
      E[v].push_back(u);
    }
    for (int u = 0; u < N; ++u) {
      if (L[u] != -1) continue;
      component[u] = u;
      dfs(u);
    }
  }
  bool is_ancestor(int u, int v) const {
    return L[u] <= L[v] && L[v] < R[u];
  }
  bool oracle(int e) const {
    return component[edges[e][0]] != component[edges[e][1]];
  }
  bool oracle(int e, int f) const {
    if (oracle(f)) return true;
    int u = edges[e][L[edges[e][0]] < L[edges[e][1]]];
    return is_ancestor(u, edges[f][0]) != is_ancestor(u, edges[f][1]);
  }
};
