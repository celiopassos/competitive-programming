// make necessary changes when T is floating point
template<typename T, int N>
T determinant(Matrix<T, N, N> A, int n) {
    T det = T(1);
    for (int x = 0; x < n; ++x) {
        int sel = -1;
        for (int i = x; i < n; ++i) {
            if (A[i][x] != T(0)) {
                sel = i;
                break;
            }
        }
        if (sel == -1) return T(0);
        if (sel != x) {
            swap(A[sel], A[x]);
            det *= T(-1);
        }
        det *= A[x][x];
        for (int i = 0; i < n; ++i) if (i != x) {
            T c = A[i][x] / A[x][x];
            for (int j = x; j < n; ++j) A[i][j] -= c * A[x][j];
        }
    }
    return det;
}
template<typename T, int N, int M>
struct GaussianElimination {
    using DomainType = Vector<T, M>;
    using CodomainType = Vector<T, N>;
    Matrix<T, N, M> A;
    Matrix<T, N, N> E;
    int n, m;
    int pivot[M], rank = 0, nullity;
    // O(min(n, m)nm)
    GaussianElimination(const Matrix<T, N, M>& A_, int n, int m) : A(A_), E(1), n(n), m(m), nullity(m) {
        fill(begin(pivot), end(pivot), -1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = -1;
            for (int i = row; i < n; ++i) {
                // for floating points take row with largest absolute value
                if (A[i][col] != T(0)) {
                    sel = i;
                    break;
                }
            }
            if (sel == -1) continue;
            if (sel != row) {
                swap(A[sel], A[row]);
                swap(E[sel], E[row]);
            }
            for (int i = 0; i < n; ++i) if (i != row) {
                T c = A[i][col] / A[row][col];
                for (int j = col; j < m; ++j) A[i][j] -= c * A[row][j];
                for (int j = 0; j < m; ++j) E[i][j] -= c * E[row][j];
            }
            pivot[col] = row++;
            ++rank, --nullity;
        }
    }
    // O(n^2 + m)
    pair<bool, DomainType> solve(CodomainType b, bool reduced = false) const {
        if (not reduced) b = E * b;
        DomainType x;
        for (int j = 0; j < m; ++j) {
            if (pivot[j] != -1) {
                x[j] = b[pivot[j]] / A[pivot[j]][j];
                b[pivot[j]] = T(0);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (b[i] != T(0)) return pair(false, x);
        }
        return pair(true, x);
    }
    // O(nullity * nm)
    vector<DomainType> kernel_basis() const {
        vector<DomainType> basis;
        DomainType e;
        for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
            e[j] = T(1);
            DomainType y = solve(A * e, true).second;
            e[j] = T(0), y[j] = T(-1);
            basis.push_back(y);
        }
        return basis;
    }
    // O(n^3)
    // assumes n == m (of course)
    Matrix<T, N, M> inverse() const {
        assert(n == m);
        assert(rank == n);
        Matrix<T, N, M> res;
        CodomainType e;
        for (int i = 0; i < n; ++i) {
            e[i] = 1;
            DomainType x = solve(e).second;
            for (int j = 0; j < n; ++j) {
                res[j][i] = x[j];
            }
            e[i] = 0;
        }
        return res;
    }
};
