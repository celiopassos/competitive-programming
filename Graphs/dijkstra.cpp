template<typename T>
bool chmin(T& x, T y) { return y < x ? (x = y, true) : false; }
template<typename T>
vector<T> dijkstra(int s, const auto& E) {
    vector<T> dist((int)size(E), numeric_limits<T>::max());
    priority_queue<pair<T, int>> pq;
    pq.emplace(dist[s] = 0, s);
    while (not empty(pq)) {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > dist[u]) continue;
        for (auto [v, w] : E[u]) {
            if (chmin(dist[v], dist[u] + w)) pq.emplace(-dist[v], v);
        }
    }
    return dist;
}
