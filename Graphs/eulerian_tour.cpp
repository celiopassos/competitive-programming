struct EulerianTour {
    int n, m = 0, odd = 0;
    vector<vector<pair<int, int>>> E;
    vector<int> deg;
    EulerianTour(int n) : n(n), E(n), deg(n) {}
    void add_edge(int u, int v) {
        int V[2] = {u, v};
        for (auto t : {0, 1}) {
            int v = V[t];
            E[v].emplace_back(V[t ^ 1], m << 1 | t);
            deg[v] += 1;
            odd += (deg[v] % 2 ? +1 : -1);
        }
        ++m;
    }
    // returns eulerian tour by vertices and edges (reversed if first bit is 1)
    pair<vector<int>, vector<int>> find(int src) const {
        assert(odd == 0);
        auto d = deg;
        vector<bool> dead(m, false);
        vector<int> ptr(n, 0), p, e;
        stack<pair<int, int>> stk;
        stk.emplace(src, -1);
        while (not stk.empty()) {
            auto [u, i] = stk.top();
            if (d[u] == 0) {
                stk.pop();
                p.push_back(u);
                if (i != -1) e.push_back(i);
            }
            else {
                for (int& l = ptr[u]; l < deg[u]; ++l) {
                    auto [v, j] = E[u][l];
                    if (not dead[j >> 1]) {
                        stk.emplace(v, j);
                        --d[u], --d[v], dead[j >> 1] = true;
                        break;
                    }
                }
            }
        }
        return {p, e};
    }
};
