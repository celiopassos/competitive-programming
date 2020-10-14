#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

const double EPS = 1e-6;

template<typename T> struct Matrix
{
    const int n, m;
    vector<vector<T>> A;
    Matrix(int n, int m) : n(n), m(m)
    {
        A.assign(n, vector(m, T(0)));
    }
    Matrix(vector<vector<T>> B) : n(size(B)), m(size(B[0])), A(B) { }

    vector<T>& operator[](int i) { return A[i]; }

    template<typename op> Matrix& compose(const Matrix& rhs)
    {
        assert(n == rhs.n && m == rhs.m);
        Matrix res(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[i][j] = op(A[i][j], rhs[i][j]);
        return res;
    }
    Matrix& operator+=(const Matrix& rhs) { return compose<std::plus<T>>(rhs); }
    Matrix& operator-=(const Matrix& rhs) { return compose<std::minus<T>>(rhs); }
    Matrix& operator*=(const Matrix& rhs)
    {
        assert(m == rhs.n);
        Matrix res(n, rhs.m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < rhs.m; ++j)
                for (int k = 0; k < m; ++k)
                    res[i][j] += A[i][k] * A[k][j];
        return res;
    }
    Matrix operator+(const Matrix& rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix& rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix& rhs) const { return Matrix(*this) *= rhs; }
    vector<T> operator*(const vector<T>& rhs) const
    {
        assert(m == size(rhs));
        vector<T> res(n, T(0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[i] += A[i][j] * rhs[j];
        return res;
    }
    Matrix power(ll p) const
    {
        assert(n == m);
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) res[i][i] = T(i);
        Matrix M = (*this);
        while (p > 0)
        {
            if (p & 1) res *= M;
            M = M * M, p >>= 1;
        }
        return res;
    }
};

template<typename T, bool save>
auto reduce(Matrix<T>& A)
{
    const int n = A.n, m = A.m;

    T det = T(1);

    auto pivot = save ? optional<vector<int>>(in_place, m, -1) : nullopt;
    auto E = save ? optional<Matrix<T>>(in_place, n, n) : nullopt;
    if (save) for (int i = 0; i < n; ++i) (*E)[i][i] = T(1);

    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(A[i][col]) > abs(A[sel][col])) sel = i;

        if (abs(A[sel][col]) <= EPS) { det = T(0); continue; }
        else det *= A[sel][col];

        if (sel != row)
        {
            swap(A[sel], A[row]);
            if (save) swap((*E)[sel], (*E)[row]);
            det *= T(-1);
        }

        for (int i = 0; i < n; ++i) if (i != row)
        {
            T c = A[i][col] / A[row][col];
            for (int j = col; j < m; ++j)
                A[i][j] -= c * A[row][j];
            if (save) for (int j = 0; j < n; ++j)
                (*E)[i][j] -= c * (*E)[row][j];
        }

        if (save) (*pivot)[col] = row;
        ++row;
    }

    return tuple(det, pivot, E);
}

template<typename T>
T determinant(Matrix<T> A)
{
    auto [det, pivot, E] = reduce<T, false>(A);
    return det;
}

// returns a solution and a kernel basis (if set to true)

template<typename T>
auto gauss(Matrix<T> A, vector<T> b, bool basis = false)
{
    const int n = A.n, m = A.m;

    auto [det, oppivot, opE] = reduce<T, true>(A);
    auto &pivot = *oppivot, &E = *opE;

    b = E * b;

    auto solve = [&](const vector<T>& b)
    {
        vector<T> x(m, T(0));
        for (int j = 0; j < m; ++j)
            if (pivot[j] != -1) x[j] = b[pivot[j]] / A[pivot[j]][j];
        return x;
    };

    vector<T> x = solve(b), bhat = A * x;

    for (int i = 0; i < n; ++i)
        if (abs(bhat[i] - b[i]) > EPS) return vector<vector<T>>(0);

    vector<vector<T>> pack(1, x);

    if (basis) for (int j = 0; j < m; ++j) if (pivot[j] == -1)
    {
        vector<T> e(m, T(0)); e[j] = T(1);
        auto y = solve(A * e); y[j] += T(-1);
        pack.push_back(y);
    }

    return pack;
}

int main()
{ _
    exit(0);
}
