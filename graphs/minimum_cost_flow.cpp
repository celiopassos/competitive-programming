// atcoder Orz
template <typename Cap, typename Cost>
struct mcf_graph {
  inline static const Cap infcap = std::numeric_limits<Cap>::max();
  inline static const Cost infcost = std::numeric_limits<Cost>::max();
  struct Edge {
    int from, to;
    Cap cap, flow;
    Cost cost;
    Cap free() const {
      return cap - flow;
    }
  };
  struct Slope {
    Cap flow;
    Cost cost, slope;
  };
  // returns the minimum cost of 'flow' units of flow
  static Cost compute_cost(const std::vector<Slope>& slopes, Cap flow) {
    auto iter = std::lower_bound(
        slopes.begin(), slopes.end(), flow,
        [](Slope sl, Cap f) { return sl.flow < f; });
    if (iter == slopes.end()) return infcost;
    return iter->cost - (iter->flow - flow) * iter->slope;
  };
  int N, M = 0;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> E;
  mcf_graph(int N) : N(N), E(N) {}
  bool negative_cost = false;
  int add_edge(int u, int v, Cap cap, Cost cost) {
    if (cost < 0) negative_cost = true;
    edges.push_back({u, v, cap, 0, cost});
    edges.push_back({v, u, 0, 0, -cost});
    E[u].push_back(M++);
    E[v].push_back(M++);
    return M - 2;
  }
  std::vector<Cost> dual_feasible(int s) const {
    if (!negative_cost) return std::vector<Cost>(N);
    std::vector<Cost> d(N, infcost);
    std::vector<bool> on(N);
    std::queue<int> q;
    q.push(s);
    on[s] = true;
    d[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      on[u] = false;
      for (auto j : E[u]) {
        if (edges[j].cap == 0) continue;
        int v = edges[j].to;
        Cost nd = d[u] + edges[j].cost;
        if (nd < d[v]) {
          d[v] = nd;
          if (!on[v]) {
            q.push(v);
            on[v] = true;
          }
        }
      }
    }
    return d;
  }
  // returns slope changing points and dual optimum
  std::pair<std::vector<Slope>, std::vector<Cost>> slope(
      int s, int t, std::vector<Cost> dual = {}) {
    if (dual.empty()) dual = dual_feasible(s);
    for (int j = 0; j < M; ++j) {
      edges[j].flow = 0;
    }
    std::vector<Cost> dist(N);
    std::vector<bool> vis(N);
    std::vector<int> p(N);
    std::vector<std::pair<Cost, int>> heap;
    heap.reserve(M);
    auto dijkstra = [&]() {
      std::fill(dist.begin(), dist.end(), infcost);
      std::fill(vis.begin(), vis.end(), false);
      heap.emplace_back(dist[s] = 0, s);
      while (!heap.empty()) {
        int u = heap[0].second;
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
        if (vis[u]) continue;
        vis[u] = true;
        if (u == t) break;
        for (auto j : E[u]) {
          if (edges[j].free() == 0) continue;
          int v = edges[j].to;
          Cost nd = dist[u] + dual[u] - dual[v] + edges[j].cost;
          if (nd < dist[v]) {
            p[v] = j;
            dist[v] = nd;
            heap.emplace_back(-dist[v], v);
            std::push_heap(heap.begin(), heap.end());
          }
        }
      }
      heap.clear();
      if (!vis[t]) return false;
      for (int u = 0; u < N; ++u) {
        if (!vis[u]) continue;
        dual[u] += dist[u] - dist[t];
      }
      return true;
    };
    std::vector<Slope> result = {{0, 0, -infcost}};
    Cap flow = 0;
    Cost cost = 0;
    while (dijkstra()) {
      Cap f = infcap;
      for (int u = t; u != s; u = edges[p[u]].from) {
        f = std::min(f, edges[p[u]].free());
      }
      for (int u = t; u != s; u = edges[p[u]].from) {
        edges[p[u]].flow += f;
        edges[p[u] ^ 1].flow -= f;
      }
      Cost d = dual[t] - dual[s];
      if (d == result.back().slope) {
        result.pop_back();
      }
      flow += f;
      cost += f * d;
      result.push_back({flow, cost, d});
    }
    return {result, dual};
  }
  // returns maximum flow, cost and dual optimum
  std::tuple<Cap, Cost, std::vector<Cost>> mincostflow(
      int s, int t, std::vector<Cost> dual_init = {}) {
    auto [slopes, dual] = slope(s, t, dual_init);
    return {slopes.back().flow, slopes.back().cost, dual};
  }
};
