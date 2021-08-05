// 2-SAT
struct SAT {
    int N;
    vector<vector<int>> E;
    SAT(int N) : N(N), E(2 * N) {}
    int neg(int u) const { return (u + N) % (2 * N); }
    void add_clause(int u, int v) {
        E[neg(u)].push_back(v);
        E[neg(v)].push_back(u);
    }
    // assumes tarjan sorts SCCs in reverse topological order (u -> v implies scc[v] <= scc[u])
    pair<bool, vector<bool>> solve() const {
        vector<bool> res(N);
        auto scc = tarjan(E);
        for (int u = 0; u < N; ++u) {
            if (scc[u] == scc[neg(u)]) return {false, {}};
            res[u] = scc[neg(u)] > scc[u];
        }
        return pair(true, res);
    }
};
