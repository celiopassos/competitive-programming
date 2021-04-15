// K > floor(log(tree height))
template<int K>
struct LCA {
    const vector<vector<int>>& E;
    const int n;
    vector<int> L, R;
    vector<array<int, K>> up;
    int timer = 0;
    void dfs(int u, int p) {
        up[u][0] = p;
        for (int i = 1; i < K; ++i) up[u][i] = up[up[u][i-1]][i-1];
        L[u] = timer;
        for (int v : E[u]) if (v != p) dfs(v, u);
        R[u] = timer++;
    }
    LCA(const auto& E, int root) : E(E), n((int)size(E)), L(n), R(n), up(n) {
        dfs(root, root);
    }
    bool is_ancestor(int u, int v) const {
        return L[u] <= L[v] && R[v] <= R[u];
    }
    int lca(int u, int v) const {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = K; i >= 0; --i) {
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }
};
