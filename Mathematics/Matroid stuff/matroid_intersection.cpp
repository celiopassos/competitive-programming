// 'heavy' matroid should be N
template<typename Matroid1, typename Matroid2>
vector<int> matroid_intersection(int n, Matroid1& M, Matroid2& N) {
    vector<bool> b(n);
    vector<int> I[2];
    while (true) {
        for (int t : {0, 1}) I[t].clear();
        for (int u = 0; u < n; ++u) {
            I[b[u]].push_back(u);
        }
        M.build(I[1]), N.build(I[1]);
        vector<bool> target(n), pushed(n);
        queue<int> q;
        for (auto u : I[0]) {
            target[u] = N.oracle(u);
            if (M.oracle(u)) {
                pushed[u] = true;
                q.push(u);
            }
        }
        vector<int> p(n, -1);
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
                if ((b[u] && M.oracle(u, v)) || (b[v] && N.oracle(v, u))) {
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
