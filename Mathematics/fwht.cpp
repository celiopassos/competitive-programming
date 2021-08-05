namespace fwht {
    template<typename T>
    using Matrix = array<array<T, 2>, 2>;
    template<typename T>
    vector<T> fwht(vector<T> v, Matrix<T> A) {
        int N = (int)v.size();
        for (int len = 1; len < N; len *= 2) {
            for (int pos = 0; pos < N; pos += 2 * len) {
                for (int i = 0; i < len; ++i) {
                    T x = v[pos + i], y = v[pos + len + i];
                    v[pos + i] = A[0][0] * x + A[0][1] * y;
                    v[pos + len + i] = A[1][0] * x + A[1][1] * y;
                }
            }
        }
        return v;
    }
    template<typename T>
    Matrix<T> or_matrix() { return {{{1, 0}, {1, 1}}}; }
    template<typename T>
    Matrix<T> and_matrix() { return {{{1, 1}, {0, 1}}}; }
    template<typename T>
    Matrix<T> xor_matrix() { return {{{+1, +1}, {+1, -1}}}; }
    template<typename T>
    Matrix<T> inverse(Matrix<T> A) {
        T det = A[0][0] * A[1][1] - A[0][1] * A[1][0];
        assert(det != T(0));
        swap(A[0][0], A[1][1]);
        A[0][1] *= -1;
        A[1][0] *= -1;
        for (int s : {0, 1}) {
            for (int t : {0, 1}) {
                A[s][t] /= det;
            }
        }
        return A;
    }
}
