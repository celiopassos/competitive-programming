// 'heavy' matroid should be M2
template<typename Matroid1, typename Matroid2>
vector<int> matroid_intersection(int N, Matroid1& M1, Matroid2& M2) {
    vector<bool> b(N);
    vector<int> I[2];
    while (true) {
        for (int t : {0, 1}) I[t].clear();
        for (int u = 0; u < N; ++u) {
            I[b[u]].push_back(u);
        }
        M1.build(I[1]), M2.build(I[1]);
        vector<bool> target(N), pushed(N);
        queue<int> q;
        for (auto u : I[0]) {
            target[u] = M2.oracle(u);
            if (M1.oracle(u)) {
                pushed[u] = true;
                q.push(u);
            }
        }
        vector<int> p(N, -1);
        bool converged = true;
        while (not q.empty()) {
            int u = q.front();
            q.pop();
            if (target[u]) {
                converged = false;
                for (int v = u; v != -1; v = p[v]) b[v] = !b[v];
                break;
            }
            for (auto v : I[!b[u]]) {
                if (pushed[v]) continue;
                if ((b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u))) {
                    p[v] = u;
                    pushed[v] = true;
                    q.push(v);
                }
            }
        }
        if (converged) break;
    }
    return I[1];
}
