template<typename T, typename Matroid1, typename Matroid2>
vector<int> weighted_matroid_intersection(int N, vector<T> w, Matroid1& M1, Matroid2& M2) {
    vector<bool> b(N), target(2 * N);
    vector<int> I[2], from(2 * N);
    vector<T> p(2 * N);
    vector<pair<T, int>> d(2 * N);
    vector<pair<pair<T, int>, int>> heap;
    auto check_edge = [&](int u, int v) {
        return (b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u));
    };
    auto relax = [&](int u, int v, T cost) {
        //assert(cost + p[u] - p[v] >= 0);
        pair<T, int> nd(d[u].first + cost + p[u] - p[v], d[u].second + 1);
        if (nd < d[v]) {
            from[v] = u;
            d[v] = nd;
            heap.emplace_back(neg(d[v]), v);
            push_heap(heap.begin(), heap.end());
        }
    };
    while (true) {
        I[0].clear(), I[1].clear();
        for (int u = 0; u < N; ++u) {
            I[b[u]].push_back(u);
        }
        M1.build(I[1]), M2.build(I[1]);
        fill(d.begin(), d.end(), pair(numeric_limits<T>::max(), numeric_limits<int>::max()));
        fill(target.begin(), target.end(), false);
        fill(from.begin(), from.end(), -1);
        for (auto u : I[0]) {
            target[u << 1 | 1] = M2.oracle(u);
            if (M1.oracle(u)) {
                d[u << 1] = {0, 0};
                heap.emplace_back(d[u << 1], u << 1);
            }
        }
        bool converged = true;
        while (!heap.empty()) {
            auto [key, u] = heap[0];
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();
            if (neg(key) != d[u]) continue;
            if (target[u]) {
                heap.clear();
                converged = false;
                for (int v = u; v != -1; v = from[from[v]]) {
                    int rv = v >> 1;
                    b[rv] = !b[rv];
                    w[rv] *= -1;
                }
                for (int v = 0; v < 2 * N; ++v) {
                    p[v] += min(d[u], d[v]).first;
                }
                break;
            }
            int ru = u >> 1;
            if (b[ru] == (u & 1)) {
                relax(u, u ^ 1, w[ru]);
            } else {
                for (auto v : I[!b[ru]]) {
                    if (check_edge(ru, v)) {
                        relax(u, v << 1 | (u & 1), 0);
                    }
                }
            }
        }
        if (converged) break;
    }
    return I[1];
}
