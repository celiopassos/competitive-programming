struct Kuhn {
    int N, M;
    std::vector<std::vector<int>> E;
    std::vector<int> matchA, matchB;
    std::vector<bool> vis;
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
            std::fill(vis.begin(), vis.end(), false);
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
    std::vector<int> left_cover() const {
        std::vector<int> U;
        for (int u = 0; u < N; ++u) {
            if (not vis[u]) {
                U.push_back(u);
            }
        }
        return U;
    }
    std::vector<int> right_cover() const {
        std::vector<int> V;
        for (int v = 0; v < M; ++v) {
            int u = matchB[v];
            if (u != -1 && vis[u]) {
                V.push_back(v);
            }
        }
        return V;
    }
};
