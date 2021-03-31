// K >= floor(log(height))

template<int K>
struct LCA {
    const vector<vector<int>>& E;
    const int n;
    vector<int> L, R, h;
    vector<array<int, K + 1>> up;
    int ct = 0;
    void dfs(int u, int p) {
        h[u] = h[p] + 1, up[u][0] = p;
        for (int i = 1; i <= K; ++i) up[u][i] = up[up[u][i-1]][i-1];
        L[u] = ct;
        for (int v : E[u]) if (v != p) dfs(v, u);
        R[u] = ct++;
    }

    LCA(const auto& E, int root) : E(E), n((int)size(E)), L(n), R(n), h(n), up(n) {
        h[root] = -1;
        dfs(root, root);
    }
    bool is_ancestor(int u, int v) const {
        return L[u] <= L[v] && R[v] <= R[u];
    }
    int query(int u, int v) const {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = K; i >= 0; --i)
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        return up[u][0];
    }
    int query(int u, int v, int root) const {
        int w[3] = { query(u, v), query(u, root), query(v, root) };
        if (w[0] == w[1]) return w[2];
        else if (w[0] == w[2]) return w[1];
        else return w[0];
    }
    int distance(int u, int v) const {
        int w = query(u, v);
        return h[u] + h[v] - 2 * h[w];
    }
    // builds virtual tree on F and returns its root and vertex set
    pair<int, vector<int>> build_virtual_tree(vector<int> V, vector<vector<int>>& F) {
        auto cmp = [&](int u, int v) { return R[u] < R[v]; };
        sort(all(V), cmp);
        int k = (int)size(V);
        for (int j = 0; j + 1 < k; ++j) V.push_back(query(V[j], V[j + 1]));
        sort(all(V), cmp);
        V.erase(unique(all(V)), end(V));
        stack<int> stk;
        for (auto u : V) {
            while (not empty(stk) && is_ancestor(u, stk.top())) {
                F[u].push_back(stk.top());
                stk.pop();
            }
            stk.push(u);
        }
        return pair(stk.top(), V);
    }
};
