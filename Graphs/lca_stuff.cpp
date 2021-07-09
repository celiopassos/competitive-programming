// lca query with custom root
template<typename LCA>
int query(int u, int v, int root, const LCA& lca) {
    int w[3] = { lca.lca(u, v), lca.lca(u, root), lca.lca(v, root) };
    if (w[0] == w[1]) return w[2];
    else if (w[0] == w[2]) return w[1];
    else return w[0];
}
// builds virtual tree on F given the vertex set V and returns its root
// V is modified to contain the new vertices and is sorted by L[u]
template<typename LCA>
int build_virtual_tree(vector<int>& V, vector<vector<int>>& F, const LCA& lca) {
    auto cmp = [&](int u, int v) { return lca.L[u] > lca.L[v]; };
    sort(begin(V), end(V), cmp);
    int k = (int)size(V);
    for (int j = 0; j + 1 < k; ++j) V.push_back(lca.lca(V[j], V[j + 1]));
    sort(begin(V), end(V), cmp), V.erase(unique(begin(V), end(V)), end(V));
    stack<int> stk;
    for (auto u : V) {
        while (not empty(stk) && lca.is_ancestor(u, stk.top())) {
            F[u].push_back(stk.top());
            stk.pop();
        }
        stk.push(u);
    }
    return stk.top();
}
