// builds virtual tree on F given the vertex set V and returns its root
// V is modified to contain the new vertices and is sorted by L[u]
template<typename LCA>
int build_virtual_tree(vector<int>& V, vector<vector<int>>& F, const LCA& lca) {
    auto cmp = [&](int u, int v) { return lca.L[u] > lca.L[v]; };
    sort(V.begin(), V.end(), cmp);
    int k = (int)V.size();
    for (int j = 0; j + 1 < k; ++j) V.push_back(lca.lca(V[j], V[j + 1]));
    sort(V.begin(), V.end(), cmp), V.erase(unique(V.begin(), V.end()), V.end());
    stack<int> stk;
    for (auto u : V) {
        while (not stk.empty() && lca.is_ancestor(u, stk.top())) {
            F[u].push_back(stk.top());
            stk.pop();
        }
        stk.push(u);
    }
    return stk.top();
}
