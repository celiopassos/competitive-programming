template<typename T>
vector<T> dijkstra(int s, const vector<vector<pair<int, T>>>& E) {
    vector<T> d(E.size(), numeric_limits<T>::max());
    priority_queue<pair<T, int>> pq;
    pq.emplace(d[s] = 0, s);
    while (not pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > d[u]) continue;
        for (auto [v, w] : E[u]) {
            T nd = d[u] + w;
            if (nd < d[v]) pq.emplace(-(d[v] = nd), v);
        }
    }
    return d;
}
