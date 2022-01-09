template <typename T>
std::vector<T> dijkstra(
    int s, const std::vector<std::vector<std::pair<int, T>>>& E) {
  std::vector<T> dist(E.size(), std::numeric_limits<T>::max());
  std::priority_queue<std::pair<T, int>> pq;
  pq.emplace(dist[s] = 0, s);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (-d > dist[u]) continue;
    for (auto [v, w] : E[u]) {
      T nd = dist[u] + w;
      if (nd < dist[v]) {
        pq.emplace(-(dist[v] = nd), v);
      }
    }
  }
  return dist;
}
