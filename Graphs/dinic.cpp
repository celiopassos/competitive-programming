template<typename T>
struct Dinic {
    inline static const T inf = numeric_limits<T>::max();
    struct Edge {
        int from, to;
        T cap, flow = 0;
        T free() const { return cap - flow; }
        Edge(int u, int v, T cap) : from(u), to(v), cap(cap) {}
    };
    vector<Edge> edges;
    int n, m = 0;
    vector<vector<int>> E;
    vector<int> level, ptr;
    Dinic(int n) : n(n), E(n), level(n), ptr(n) {}
    int add_edge(int u, int v, T cap) {
        assert(cap >= 0);
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        E[u].push_back(m++);
        E[v].push_back(m++);
        return m - 2;
    }
    bool bfs(int s, int t) {
        fill(begin(level), end(level), -1);
        level[s] = 0;
        static queue<int> q;
        q.push(s);
        while (not q.empty()) {
            int u = q.front();
            q.pop();
            for (auto j : E[u]) {
                int v = edges[j].to;
                if (level[v] != -1 || edges[j].free() <= 0) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }
    T push(int u, int t, T pushed) {
        if (u == t || pushed == 0) return pushed;
        for (int& i = ptr[u]; i < (int)size(E[u]); ++i) {
            auto &edge = edges[E[u][i]], &back = edges[E[u][i] ^ 1];
            if (level[edge.to] != level[u] + 1 || edge.free() <= 0) continue;
            T pushing = push(edge.to, t, min(pushed, edge.free()));
            if (pushing == 0) continue;
            edge.flow += pushing, back.flow -= pushing;
            return pushing;
        }
        return 0;
    }
    T flow(int s, int t) {
        for (auto& edge : edges) edge.flow = 0;
        T f = 0;
        while (bfs(s, t)) {
            fill(begin(ptr), end(ptr), 0);
            while (T pushed = push(s, t, inf)) f += pushed;
        }
        return f;
    }
    bool cut(int j) const {
        return edges[j].free() == 0 && level[edges[j].from] != -1 && level[edges[j].to] == -1;
    }
};
