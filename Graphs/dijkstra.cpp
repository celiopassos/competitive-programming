template<typename T>
vector<T> dijkstra(int s, const vector<vector<pair<int, T>>>& E) {
    vector<T> dist(E.size(), numeric_limits<T>::max());
    priority_queue<pair<T, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (not pq.empty()) {
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
