// needs Z2GaussianElimination
template<int N>
struct Z2Matroid {
    vector<bitset<N>> matrix;
    vector<int> idx;
    Z2GaussianElimination<N> basis;
    Z2Matroid(const vector<bitset<N>> matrix) : matrix(matrix), idx(size(matrix)) {}
    void build(const vector<int>& I) {
        basis = Z2GaussianElimination<N>();
        int rk = 0;
        for (auto u : I) {
            assert(basis.insert(matrix[u]));
            idx[u] = rk++;
        }
    }
    bool oracle(int u) const {
        return !basis.solve(matrix[u]).first;
    }
    bool oracle(int u, int v) const {
        auto [good, coef] = basis.solve(matrix[v]);
        return !good || coef[idx[u]];
    }
};
