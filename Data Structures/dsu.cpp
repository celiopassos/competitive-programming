struct DSU {
    std::vector<int> p, rk;
    DSU(int N) : p(N), rk(N) {
        std::iota(p.begin(), p.end(), 0);
    }
    int find(int u) {
        return p[u] == u ? u : p[u] = find(p[u]);
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rk[u] < rk[v]) {
            std::swap(u, v);
        }
        p[v] = u, rk[u] += (rk[u] == rk[v]);
    }
};
