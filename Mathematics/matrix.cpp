using ld = long double;

const ld EPS = 1e-5;

// may wanna use T = long double

template<typename T>
T templatepow(T x, ll p)
{
    assert(p >= 0);
    T res(1);
    while (p > 0)
    {
        if (p & 1) res = res * x;
        x = x * x, p >>= 1;
    }
    return res;
}

template<typename T, int N, int M>
struct Matrix
{
    T A[N][M];
    int row[N];

    Matrix()
    {
        fill(&A[0][0], &A[0][0] + N * M, T(0));
        iota(all(row), 0);
    }
    Matrix(T value) : Matrix()
    {
        for (int i = 0; i < min(N, M); ++i) A[i][i] = value;
    }
    Matrix(initializer_list<initializer_list<T>> lst) : Matrix()
    {
        int i = 0, j = 0;
        for (const auto& v : lst)
        {
            for (const auto& x : v) A[i][j++] = x;
            i++, j = 0;
        }
    }

    T* operator[](int i) { return A[row[i]]; }
    const T* operator[](int i) const { return A[row[i]]; }

    void swap_rows(int i, int j) { swap(row[i], row[j]); }

    template<typename Op> Matrix& compose(const Matrix& rhs, Op&& op)
    {
        auto& lhs = *this;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                lhs[i][j] = op(lhs[i][j], rhs[i][j]);
        return *this;
    }
    Matrix& operator+=(const Matrix& rhs) { return compose(rhs, std::plus<T>()); }
    Matrix& operator-=(const Matrix& rhs) { return compose(rhs, std::minus<T>()); }
    Matrix operator+(const Matrix& rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix& rhs) const { return Matrix(*this) -= rhs; }
    template<int K> Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const
    {
        const auto& lhs = *this;
        Matrix<T, N, K> res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < K; ++j)
                for (int k = 0; k < M; ++k)
                    res[i][j] += lhs[i][k] * rhs[k][j];
        return res;
    }
    friend Matrix operator*(const T& alpha, Matrix A)
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] *= alpha;
        return A;
    }
};

template<typename T, int N>
struct Vector : public Matrix<T, N, 1>
{
    using Base = Matrix<T, N, 1>;

    Vector() : Base() { }
    Vector(const Base& v) : Base(v) { }

    T& operator[](int i) { return Base::operator[](i)[0]; }
    const T& operator[](int i) const { return Base::operator[](i)[0]; }
};

template<typename T, int N, int M>
struct Affine
{
    Matrix<T, N, M> A;
    Vector<T, N> b;

    Affine(T value = T(0)) : A(value) { }
    Affine(const Matrix<T, N, M>& A) : A(A) { }

    Affine operator+=(const Affine& rhs) { A += rhs.A, b += rhs.B; }
    Affine operator-=(const Affine& rhs) { A -= rhs.A, b -= rhs.B; }
    Affine operator+(const Affine& rhs) const { return Affine(*this) += rhs; };
    Affine operator-(const Affine& rhs) const { return Affine(*this) -= rhs; };

    T* operator[](int i) { return A[i]; }
    const T* operator[](int i) const { return A[i]; }

    template<int K>
        Affine<T, N, K> operator*(const Affine<T, M, K>& rhs)
        {
            Affine<T, N, K> res;

            res.A = A * rhs.A;
            res.b = A * rhs.b + b;

            return res;
        }
    Vector<T, N> operator*(const Vector<T, M>& x) const
    {
        return A * x + b;
    }
};

template<typename T, int N>
T determinant(Matrix<T, N, N> A, int n = N)
{
    T det = T(1);

    for (int x = 0; x < n; ++x)
    {
        int sel = -1;
        for (int i = x; i < n; ++i)
            if (abs(A[i][x]) > EPS)
            {
                sel = i;
                break;
            }

        if (sel == -1) return T(0);
        else det *= A[sel][x];

        if (sel != x) A.swap_rows(sel, x), det *= T(-1);

        for (int i = 0; i < n; ++i) if (i != x)
        {
            T c = A[i][x] / A[x][x];
            for (int j = x; j < n; ++j) A[i][j] -= c * A[x][j];
        }
    }

    return det;
}

enum Classification { Unique, Infinite, None };

// returns a solution and a kernel basis (if set to true)
// uncomment lines and save the matrix E to solve several systems in O(N^2) each

template<typename T, int N, int M>
auto gauss(Matrix<T, N, M> A, Vector<T, N> b, bool kernel_basis = false, int n = N, int m = M)
{
    using DomainType = Vector<T, M>;
    using CodomainType = Vector<T, N>;

    //Matrix<T, N, N> E(T(1));
    int pivot[M]; fill(all(pivot), -1);

    Classification cl = Unique;

    for (int col = 0, row = 0; col < m && row < n; ++col)
    {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(A[i][col]) > abs(A[sel][col])) sel = i;

        if (abs(A[sel][col]) <= EPS)
        {
            cl = Infinite;
            continue;
        }

        if (sel != row)
        {
            A.swap_rows(sel, row), swap(b[sel], b[row]);
            //E.swap_rows(sel, row);
        }

        for (int i = 0; i < n; ++i) if (i != row)
        {
            T c = A[i][col] / A[row][col];
            for (int j = col; j < m; ++j) A[i][j] -= c * A[row][j];
            //for (int j = 0; j < m; ++j) E[i][j] -= c * E[row][j];
            b[i] -= c * b[row];
        }

        pivot[col] = row++;
    }

    auto solve = [&](const Vector<T, N>& b)
    {
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

    if (kernel_basis) for (int j = 0; j < m; ++j) if (pivot[j] == -1)
    {
        e[j] = T(1);
        DomainType y = solve(A * e);
        e[j] = T(0), y[j] = T(-1);
        basis.push_back(y);
    }

    return tuple(cl, x, basis);
}
