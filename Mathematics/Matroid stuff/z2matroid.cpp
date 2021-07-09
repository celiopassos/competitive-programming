// needs XORBasis
template<int N>
struct Z2Matroid {
    vector<bitset<N>> matrix;
    int M;
    XORBasis<N> basis;
    vector<int> idx;
    Z2Matroid(const vector<bitset<N>> matrix) : matrix(matrix), M((int)size(matrix)), idx(M) {}
    void build(const vector<int>& I) {
        basis = XORBasis<N>();
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
