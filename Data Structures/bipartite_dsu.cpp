struct DSU {
    vector<int> p, rk, color, bipartite;
    DSU(int n) : p(n), rk(n), color(n), bipartite(n, 1) {
        iota(begin(p), end(p), 0);
    };
    int find(int u) {
        if (u == p[u]) return u;
        int v = find(p[u]);
        color[u] ^= color[p[u]];
        return p[u] = v;
    }
    int find_color(int u) {
        find(u);
        return color[u];
    }
    // check if it doesn't create an odd cycle
    bool can(int u, int v) {
        return find(u) != find(v) || color[u] != color[v];
    }
    void unite(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) {
            if (color[u] == color[v]) bipartite[pu] = false;
            return;
        }
        if (rk[pu] < rk[pv]) swap(pu, pv);
        if (color[u] == color[v]) color[pv] ^= 1;
        p[pv] = pu, rk[pu] += (rk[pu] == rk[pv]);
        if (not bipartite[pv]) bipartite[pu] = false;
    }
};
