// 'heavy' matroid should be M2
template<typename T, typename Matroid1, typename Matroid2>
vector<int> weighted_matroid_intersection(int N, const vector<T>& w, Matroid1& M1, Matroid2& M2) {
    vector<bool> b(N), target(N);
    vector<int> I[2], p(N);
    vector<T> l(N);
    vector<vector<int>> E(N);
    vector<pair<T, int>> d(N);
    queue<int> q;
    while (true) {
        for (int t : {0, 1}) I[t].clear();
        for (int u = 0; u < N; ++u) {
            I[b[u]].push_back(u);
            l[u] = (b[u] ? -1 : +1) * w[u];
        }
        M1.build(I[1]), M2.build(I[1]);
        for (int u = 0; u < N; ++u) {
            E[u].clear();
            for (auto v : I[!b[u]]) {
                if ((b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u))) {
                    E[u].push_back(v);
                }
            }
        }
        fill(d.begin(), d.end(), pair(numeric_limits<T>::max(), numeric_limits<int>::max()));
        fill(target.begin(), target.end(), false);
        fill(p.begin(), p.end(), -1);
        for (auto u : I[0]) {
            target[u] = M2.oracle(u);
            if (M1.oracle(u)) {
                q.push(u);
                d[u] = {w[u], 0};
            }
        }
        int t = -1;
        while (not q.empty()) {
            int u = q.front();
            q.pop();
            if (target[u] && (t == -1 || d[t] > d[u])) t = u;
            for (auto v : E[u]) {
                pair<T, int> nd(d[u].first + l[v], d[u].second + 1);
                if (nd < d[v]) {
                    p[v] = u;
                    d[v] = nd;
                    q.push(v);
                }
            }
        }
        if (t == -1) break;
        for (int v = t; v != -1; v = p[v]) b[v] = !b[v];
    }
    return I[1];
}
