// 2-SAT
struct SAT {
    const int n;
    vector<vector<int>> E;

    SAT(int n) : n(n), E(2 * n) {}

    int neg(int u) const { return (u + n) % (2 * n); }
    void add_clause(int u, int v) {
        E[neg(u)].push_back(v);
        E[neg(v)].push_back(u);
    }
    // assumes tarjan sorts SCCs in reverse topological order (u -> v implies scc[v] <= scc[u])
    pair<bool, vector<bool>> solve() const {
        vector<bool> res(n);
        auto scc = tarjan(E);
        for (int u = 0; u < n; ++u) {
            if (scc[u] == scc[neg(u)]) return {false, {}};
            res[u] = scc[neg(u)] > scc[u];
        }
        return pair(true, res);
    }
};
