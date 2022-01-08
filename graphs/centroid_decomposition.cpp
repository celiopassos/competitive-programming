// K > centroid tree height, or simply log(N)
template<int K>
struct CentroidDecomposition {
    const std::vector<std::vector<int>>& E;
    int N, root;
    std::vector<int> sz, p, subtree, dead, level;
    std::vector<std::array<int, K>> dist;
    int timer;
    void dfs(int u, int p, int k) {
        sz[u] = 1;
        for (auto v : E[u]) {
            if (v == p || dead[v]) continue;
            dist[v][k] = dist[u][k] + 1;
            dfs(v, u, k);
            sz[u] += sz[v];
        }
    }
    int find_centroid(int u, int p, int need) const {
        for (auto v : E[u]) {
            if (v == p || dead[v]) continue;
            if (sz[v] > need) return find_centroid(v, u, need);
        }
        return u;
    }
    CentroidDecomposition(const std::vector<std::vector<int>>& E_) :
        E(E_), N(E.size()), sz(N), p(N, -1), subtree(N), dead(N), level(N), dist(N) {
        std::queue<int> q;
        dfs(0, -1, 0);
        root = find_centroid(0, -1, N / 2);
        q.push(root);
        dist[root][0] = 0;
        while (not q.empty()) {
            int rt = q.front();
            q.pop();
            dead[rt] = true;
            int k = level[rt];
            dfs(rt, -1, level[rt]);
            for (auto v : E[rt]) {
                if (dead[v]) continue;
                int u = find_centroid(v, -1, sz[v] / 2);
                p[u] = rt;
                level[u] = k + 1;
                subtree[u] = v;
                q.push(u);
            }
        }
    }
    int operator[](int u) const {
        return p[u];
    }
    int lca(int u, int v) const {
        if (level[u] < level[v]) std::swap(u, v);
        while (level[u] > level[v]) u = p[u];
        while (u != v) u = p[u], v = p[v];
        return u;
    }
    int distance(int u, int v) const {
        int w = lca(u, v);
        return dist[u][level[w]] + dist[v][level[w]];
    }
};
