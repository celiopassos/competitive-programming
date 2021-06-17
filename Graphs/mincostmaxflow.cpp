template<typename T>
bool chmin(T& x, T y) { return y < x ? (x = y, true) : false; }
template<typename T>
struct better_queue : public priority_queue<T> {
    void clear() { this->c.clear(); }
};
template<typename Cap, typename Cost>
struct MCMF {
    struct Edge {
        int from, to;
        Cap cap, flow = 0;
        Cost cost;
        Edge(int u, int v, Cap cap, Cost cost) :
            from(u), to(v), cap(cap), cost(cost) {}
        Cap free() const { return cap - flow; }
    };
    const int n;
    const Cap infcap = numeric_limits<Cap>::max();
    const Cost infcost = numeric_limits<Cost>::max();
    vector<Edge> edges;
    vector<vector<int>> E;
    MCMF(int n) : n(n) {
        E.resize(n);
        pi.resize(n), dist.resize(n);
        vis.resize(n), parent.resize(n);
    }
    int m = 0;
    bool negative = false;
    void add_edge(int u, int v, Cap cap, Cost cost) {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        E[u].push_back(m++);
        E[v].push_back(m++);
        if (cost < 0) negative = true;
    }
    vector<Cost> pi, dist;
    vector<int> parent, vis;
    bool fix_potentials(int t) {
        if (not vis[t]) return false;
        for (int u = 0; u < n; ++u)
            if (vis[u]) pi[u] += dist[u] - dist[t];
        return true;
    }
    bool spfa(int s, int t, bool fix = false) {
        fill(begin(dist), end(dist), infcost), fill(begin(parent), end(parent), 0), fill(begin(vis), end(vis), 0);
        static queue<int> q; q.push(s); dist[s] = 0;
        while (not q.empty()) {
            int v = q.front(); q.pop(); vis[v] = 1;
            for (auto idx : E[v]) {
                const auto& edge = edges[idx];
                if (not edge.free()) continue;
                if (chmin(dist[edge.to], dist[v] + edge.cost)) {
                    parent[edge.to] = idx;
                    q.push(edge.to);
                }
            }
        }
        if (fix) return fix_potentials(t);
        else return vis[t];
    }
    bool dijkstra(int s, int t) {
        fill(begin(dist), end(dist), infcost), fill(begin(parent), end(parent), 0), fill(begin(vis), end(vis), 0);
        struct Q {
            Cost key; int v;
            Q(Cost key, int v) : key(key), v(v) {}
            bool operator<(Q rhs) const { return key > rhs.key; }
        };
        static better_queue<Q> pq; pq.emplace(0, s); dist[s] = 0;
        while (not pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (vis[v]++) continue;
            if (v == t) { pq.clear(); break; }
            for (auto idx : E[v]) {
                const auto& edge = edges[idx];
                if (vis[edge.to] || not edge.free()) continue;
                Cost cost = edge.cost + pi[v] - pi[edge.to];
                if (chmin(dist[edge.to], dist[v] + cost)) {
                    parent[edge.to] = idx;
                    pq.emplace(dist[edge.to], edge.to);
                }
            }
        }
        return fix_potentials(t);
    }
    pair<Cap, Cost> flow(int s, int t) {
        for (auto& edge : edges) edge.flow = 0;
        fill(begin(pi), end(pi), 0);
        if (negative) spfa(s, t, true);
        Cap flow = 0;
        Cost cost = 0;
        while (dijkstra(s, t)) {
            Cap pushed = infcap;
            Cost price = 0;
            for (int v = t; v != s; v = edges[parent[v]].from)
                chmin(pushed, edges[parent[v]].free());
            for (int v = t; v != s; v = edges[parent[v]].from) {
                auto &edge = edges[parent[v]], &back = edges[parent[v] ^ 1];
                edge.flow += pushed, back.flow -= pushed;
                price += edge.cost;
            }
            flow += pushed, cost += price * pushed;
        }
        return { flow, cost };
    }
};
