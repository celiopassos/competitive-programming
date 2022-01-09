struct EulerianTour {
  int N, M = 0, odd = 0;
  std::vector<std::vector<std::pair<int, int>>> E;
  std::vector<int> deg;
  EulerianTour(int N) : N(N), E(N), deg(N) {}
  void add_edge(int u, int v) {
    int V[2] = {u, v};
    for (auto t : {0, 1}) {
      int v = V[t];
      E[v].emplace_back(V[t ^ 1], M << 1 | t);
      deg[v] += 1;
      odd += (deg[v] % 2 ? +1 : -1);
    }
    ++M;
  }
  // returns eulerian tour by vertices and edges (reversed if first bit is 1)
  std::pair<std::vector<int>, std::vector<int>> find(int src) const {
    assert(odd == 0);
    auto d = deg;
    std::vector<bool> dead(M, false);
    std::vector<int> ptr(N, 0), p, e;
    std::stack<std::pair<int, int>> stk;
    stk.emplace(src, -1);
    while (!stk.empty()) {
      auto [u, i] = stk.top();
      if (d[u] == 0) {
        stk.pop();
        p.push_back(u);
        if (i != -1) e.push_back(i);
      } else {
        for (int& l = ptr[u]; l < deg[u]; ++l) {
          auto [v, j] = E[u][l];
          if (!dead[j >> 1]) {
            stk.emplace(v, j);
            --d[u], --d[v], dead[j >> 1] = true;
            break;
          }
        }
      }
    }
    return {p, e};
  }
};
