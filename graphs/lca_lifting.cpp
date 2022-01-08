// K > floor(log(tree height))
template<int K>
struct LCA {
    const std::vector<std::vector<int>>& E;
    int N;
    std::vector<int> L, R, inv, h;
    std::vector<std::array<int, K>> up;
    int timer = 0;
    void dfs(int u, int p) {
        up[u][0] = p;
        for (int i = 0; i + 1 < K; ++i) up[u][i + 1] = up[up[u][i]][i];
        inv[L[u] = timer++] = u;
        for (int v : E[u]) {
            if (v == p) continue;
            h[v] = h[u] + 1;
            dfs(v, u);
        }
        R[u] = timer;
    }
    LCA(const std::vector<std::vector<int>>& E, int root) : E(E), N(E.size()), L(N), R(N), inv(N), h(N), up(N) {
        dfs(root, root);
    }
    bool is_ancestor(int u, int v) const {
        return L[u] <= L[v] && R[v] <= R[u];
    }
    int lca(int u, int v) const {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = K - 1; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }
    int dist(int u, int v) const {
        int w = lca(u, v);
        return h[u] + h[v] - 2 * h[w];
    }
};
