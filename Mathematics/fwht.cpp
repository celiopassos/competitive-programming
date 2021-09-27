namespace fwht {
    template<typename T>
    using matrix = array<array<T, 2>, 2>;
    template<typename T>
    matrix<T> adjugate(matrix<T> M) {
        swap(M[0][0], M[1][1]);
        M[0][1] *= -1;
        M[1][0] *= -1;
        return M;
    }
    template<typename T>
    T determinant(matrix<T> M) {
        return M[0][0] * M[1][1] - M[0][1] * M[1][0];
    }
    template<typename T>
    matrix<T> inverse(matrix<T> M) {
        T det = determinant(M);
        for (int s : {0, 1}) {
            for (int t : {0, 1}) {
                M[s][t] /= det;
            }
        }
    }
    template<typename T>
    vector<T> fwht(vector<T> v, matrix<T> M) {
        int N = (int)v.size();
        for (int len = 1; len < N; len *= 2) {
            for (int pos = 0; pos < N; pos += 2 * len) {
                for (int i = 0; i < len; ++i) {
                    T x = v[pos + i], y = v[pos + len + i];
                    v[pos + i] = M[0][0] * x + M[0][1] * y;
                    v[pos + len + i] = M[1][0] * x + M[1][1] * y;
                }
            }
        }
        return v;
    }
    template<typename T>
    vector<T> convolution(const vector<T>& a, const vector<T>& b, matrix<T> M) {
        auto ahat = fwht(a, M), bhat = fwht(b, M);
        int N = (int)a.size();
        for (int i = 0; i < N; ++i) {
            ahat[i] *= bhat[i];
        }
        auto c = fwht(ahat, adjugate(M));
        T det = determinant(M), p = 1;
        for (int len = 1; len < N; len <<= 1) {
            p *= det;
        }
        for (int i = 0; i < N; ++i) {
            c[i] /= p;
        }
        return c;
    }
    template<typename T>
    matrix<T> or_matrix() { return {{{1, 0}, {1, 1}}}; }
    template<typename T>
    matrix<T> and_matrix() { return {{{1, 1}, {0, 1}}}; }
    template<typename T>
    matrix<T> xor_matrix() { return {{{+1, +1}, {+1, -1}}}; }
}
