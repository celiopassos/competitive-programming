struct TreeDecomposition {
    const vector<vector<int>>& E;
    int N, root, K;
    vector<int> block, p, L, R;
    int num_blocks = 0;
    void mark(vector<int>& S) {
        for (auto u : S) {
            block[u] = num_blocks;
        }
        ++num_blocks;
        S.clear();
    }
    int timer = 0;
    vector<int> decompose(int u) {
        L[u] = timer++;
        vector<int> S;
        for (auto v : E[u]) {
            if (v == p[u]) continue;
            p[v] = u;
            auto R = decompose(v);
            S.insert(end(S), begin(R), end(R));
            if ((int)S.size() > K) mark(S);
        }
        R[u] = timer;
        S.push_back(u);
        return S;
    }
    // O(N * K)
    TreeDecomposition(const vector<vector<int>>& E, int root, int K) : E(E), N((int)E.size()), root(root), K(K), block(N), p(N, -1), L(N), R(N) {
        auto S = decompose(root);
        if (not S.empty()) mark(S);
    }
    bool is_ancestor(int u, int v) const {
        return L[u] <= L[v] && R[v] <= R[u];
    }
    template<typename Update>
    void traverse(array<int, 2> P, Update&& update) const {
        for (int t : {0, 1}) {
            while (not is_ancestor(P[t], P[t ^ 1])) {
                update(P[t]);
                P[t] = p[P[t]];
            }
        }
    }
    // O(N^2 / K + Q.size() * K)
    template<typename Evaluate, typename Update>
    void run(const vector<array<int, 2>>& Q, Evaluate&& evaluate, Update&& update) const {
        vector<int> Z(Q.size());
        iota(begin(Z), end(Z), 0);
        auto key = [&](int i) { return pair<int, int>(block[Q[i][0]], L[Q[i][1]]); };
        sort(begin(Z), end(Z), [&](int i, int j) { return key(i) < key(j); });
        array<int, 2> P = {0, 0};
        for (auto z : Z) {
            for (int t : {0, 1}) {
                traverse({P[t], Q[z][t]}, update);
                P[t] = Q[z][t];
            }
            evaluate(z);
        }
    }
};
