template<int N> struct XORBasis {
    using V = bitset<N>;
    array<V, N> basis, alpha;
    int dim = 0;
    auto reduce(V& x) const {
        V coef;
        for (int i = N - 1; i >= 0 && x.any(); --i) {
            if (x[i] == 0) continue;
            if (basis[i] == 0) return pair(i, coef);
            x ^= basis[i], coef ^= alpha[i];
        }
        return pair(-1, coef);
    }
    bool insert(V x) {
        auto [i, coef] = reduce(x);
        if (i == -1) return false;
        basis[i] = x, dim += 1;
        alpha[i] = coef;
        alpha[i][dim - 1] = 1;
        return true;
    }
    auto solve(V x) const {
        auto [i, coef] = reduce(x);
        return pair(i == -1, coef);
    }
};
