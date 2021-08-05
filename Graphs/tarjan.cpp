// returns a vector scc where scc[u] == scc[v] iff
// u and v lie in the same strongly connected component
//
// these ids are already sorted topologically in reverse order
// i.e., scc's with 0 out-degree first
// it is guarenteed that 0 <= scc[u] < n for all u
vector<int> tarjan(const vector<vector<int>>& E) {
    int n = (int)E.size(), timer = 0, ct = 0;
    enum State { unvisited, active, visited };
    vector<State> state(n, unvisited);
    vector<int> low(n, -1), num(n, -1), scc(n, -1);
    stack<int> stk;
    auto dfs = [&](auto& self, int u) -> void {
        low[u] = num[u] = timer++, state[u] = active;
        stk.push(u);
        for (auto v : E[u]) {
            if (state[v] == unvisited) self(self, v);
            if (state[v] == active) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            do {
                int v = stk.top(); stk.pop();
                scc[v] = ct, state[v] = visited;
            } while (not stk.empty() && num[stk.top()] >= num[u]);
            ++ct;
        }
    };
    for (int u = 0; u < n; ++u) if (num[u] == -1) dfs(dfs, u);
    return scc;
}
