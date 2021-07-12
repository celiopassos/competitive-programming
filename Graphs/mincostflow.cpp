template<typename Cap, typename Cost>
struct mcf_graph {
    inline static const Cap infcap = numeric_limits<Cap>::max();
    inline static const Cost infcost = numeric_limits<Cost>::max();
    struct Edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
        Cap free() const { return cap - flow; }
    };
    struct Slope {
        Cap flow;
        Cost cost, slope;
    };
    // cost of 'flow' units of flow
    static Cost compute_cost(const vector<Slope>& slopes, Cap flow) {
        auto iter = lower_bound(begin(slopes), end(slopes), flow, [](Slope sl, Cap f) { return sl.flow < f; });
        if (iter == end(slopes)) return infcost;
        return iter->cost - (iter->flow - flow) * iter->slope;
    };
    int N, M = 0;
    vector<Edge> edges;
    vector<vector<int>> E;
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
    vector<Cost> dual_feasible(int s) const {
        if (not negative_cost) return vector<Cost>(N);
        vector<Cost> d(N, infcost);
        vector<bool> on(N);
        queue<int> q;
        q.push(s);
        on[s] = true;
        d[s] = 0;
        while (not empty(q)) {
            int u = q.front();
            q.pop();
            on[u] = false;
            for (auto j : E[u]) {
                if (edges[j].cap == 0) continue;
                int v = edges[j].to;
                Cost nd = d[u] + edges[j].cost;
                if (nd < d[v]) {
                    d[v] = nd;
                    if (not on[v]) {
                        q.push(v);
                        on[v] = true;
                    }
                }
            }
        }
        return d;
    }
    // returns slope changing points and dual optimum
    pair<vector<Slope>, vector<Cost>> slope(int s, int t, vector<Cost> dual = {}, Cap limit = infcap) {
        if (empty(dual)) dual = dual_feasible(s);
        for (int j = 0; j < M; ++j) {
            edges[j].flow = 0;
        }
        vector<Cost> dist(N);
        vector<int> p(N);
        vector<pair<Cost, int>> heap;
        heap.reserve(M);
        auto push = [&](int v) {
            heap.push_back({-dist[v], v});
            push_heap(begin(heap), end(heap));
        };
        auto pop = [&]() {
            auto p = heap[0];
            pop_heap(begin(heap), end(heap));
            heap.pop_back();
            return p;
        };
        auto dijkstra = [&]() {
            fill(begin(dist), end(dist), infcost);
            dist[s] = 0;
            push(s);
            while (not empty(heap)) {
                auto [d, u] = pop();
                if (-d > dist[u]) continue;
                for (auto j : E[u]) {
                    if (edges[j].free() == 0) continue;
                    int v = edges[j].to;
                    Cost nd = dist[u] + dual[u] - dual[v] + edges[j].cost;
                    if (nd < dist[v]) {
                        dist[v] = nd;
                        p[v] = j;
                        push(v);
                    }
                }
            }
            if (dist[t] == infcost) return false;
            for (int u = 0; u < N; ++u) {
                if (dist[u] == infcost) continue;
                dual[u] += dist[u];
            }
            return true;
        };
        vector<Slope> result = {{0, 0, 0}};
        Cap flow = 0;
        Cost cost = 0;
        while (flow < limit && dijkstra()) {
            Cap f = limit - flow;
            for (int u = t; u != s; u = edges[p[u]].from) {
                f = min(f, edges[p[u]].free());
            }
            for (int u = t; u != s; u = edges[p[u]].from) {
                edges[p[u]].flow += f;
                edges[p[u] ^ 1].flow -= f;
            }
            if (dual[t] == result.back().slope) {
                result.pop_back();
            }
            flow += f;
            cost += f * dual[t];
            result.push_back({flow, cost, dual[t]});
        }
        return {result, dual};
    }
    // returns maximum flow, cost and dual optimum
    tuple<Cap, Cost, vector<Cost>> mincostflow(int s, int t, vector<Cost> dual_init = {}, Cap limit = infcap) {
        auto [slopes, dual] = slope(s, t, dual_init, limit);
        return {slopes.back().flow, slopes.back().cost, dual};
    }
};
