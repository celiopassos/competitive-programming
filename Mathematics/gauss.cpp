template<typename T, int N>
T determinant(Matrix<T, N, N> A, int n = N) {
    T det = T(1);

    for (int x = 0; x < n; ++x) {
        int sel = -1;
        for (int i = x; i < n; ++i)
            if (abs(A[i][x]) > EPS) {
                sel = i;
                break;
            }

        if (sel == -1) return T(0);
        else det *= A[sel][x];

        if (sel != x) A.swap_rows(sel, x), det *= T(-1);

        for (int i = 0; i < n; ++i) if (i != x) {
            T c = A[i][x] / A[x][x];
            for (int j = x; j < n; ++j) A[i][j] -= c * A[x][j];
        }
    }

    return det;
}

enum Classification { Unique, Infinite, None };

// returns a solution and a kernel basis (if set to true)
// uncomment lines and save the matrix E to solve several systems in O(N^2) each
//
// may wanna use T = long double

const long double EPS = 1e-5;

template<typename T, int N, int M>
auto gauss(Matrix<T, N, M> A, Vector<T, N> b, bool kernel_basis = false, int n = N, int m = M) {
    using DomainType = Vector<T, M>;
    using CodomainType = Vector<T, N>;

    //Matrix<T, N, N> E(T(1));
    int pivot[M]; fill(all(pivot), -1);

    Classification cl = Unique;

    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(A[i][col]) > abs(A[sel][col])) sel = i;

        if (abs(A[sel][col]) <= EPS) {
            cl = Infinite;
            continue;
        }

        if (sel != row) {
            A.swap_rows(sel, row), swap(b[sel], b[row]);
            //E.swap_rows(sel, row);
        }

        for (int i = 0; i < n; ++i) if (i != row) {
            T c = A[i][col] / A[row][col];
            for (int j = col; j < m; ++j) A[i][j] -= c * A[row][j];
            //for (int j = 0; j < m; ++j) E[i][j] -= c * E[row][j];
            b[i] -= c * b[row];
        }

        pivot[col] = row++;
    }

    auto solve = [&](const Vector<T, N>& b) {
        DomainType x;
        for (int j = 0; j < m; ++j)
            if (pivot[j] != -1) x[j] = b[pivot[j]] / A[pivot[j]][j];
        return x;
    };

    DomainType x = solve(b);
    vector<DomainType> basis;

    CodomainType bhat = A * x;

    for (int i = 0; i < n; ++i)
        if (abs(bhat[i] - b[i]) > EPS) return tuple(None, x, basis);

    DomainType e; 

    if (kernel_basis) for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
        e[j] = T(1);
        DomainType y = solve(A * e);
        e[j] = T(0), y[j] = T(-1);
        basis.push_back(y);
    }

    return tuple(cl, x, basis);
}
