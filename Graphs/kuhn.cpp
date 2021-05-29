struct Kuhn {
    int N, M;
    vector<vector<int>> E;
    vector<int> matchA, matchB;
    vector<bool> vis;
    Kuhn(int N, int M) : N(N), M(M), E(N), matchA(N, -1), matchB(M, -1), vis(N) {}
    void add_edge(int u, int v) {
        E[u].push_back(v);
    }
    bool augment(int u) {
        vis[u] = true;
        for (auto v : E[u]) {
            int w = matchB[v];
            if (w == -1 || (not vis[w] && augment(w))) {
                matchA[u] = v, matchB[v] = u;
                return true;
            }
        }
        return false;
    }
    int mx = 0;
    int maximum_matching() {
        while (true) {
            bool converged = true;
            fill(all(vis), false);
            for (int u = 0; u < N; ++u) {
                if (not vis[u] && matchA[u] == -1 && augment(u)) {
                    converged = false;
                    ++mx;
                }
            }
            if (converged) break;
        }
        return mx;
    }
    vector<int> left_cover() const {
        vector<int> U;
        for (int u = 0; u < N; ++u) {
            if (not vis[u]) U.push_back(u);
        }
        return U;
    }
    vector<int> right_cover() const {
        vector<int> V;
        for (int v = 0; v < M; ++v) {
            int u = matchB[v];
            if (u != -1 && vis[u]) V.push_back(v);
        }
        return V;
    }
};
