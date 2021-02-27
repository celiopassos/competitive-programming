bool chmin(auto& x, auto y) { return y < x ? (x = y, true) : false; }

template<typename T>
vector<T> dijkstra(int s, const auto& E)
{
    vector<T> dist(size(E), T(LINF));
    priority_queue<Data> pq;
    pq.emplace(dist[s] = 0, s);
    while (not empty(pq))
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > dist[u]) continue;
        for (auto [v, w] : E[u])
        {
            if (chmin(dist[v], dist[u] + w)) pq.emplace(-dist[v], v);
        }
    }
    return dist;
}
