#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

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

template<typename T, int N, int M> struct Matrix
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
    template<int K>
    Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const
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

template<typename T, int N> struct Vector : public Matrix<T, N, 1>
{
    using Base = Matrix<T, N, 1>;

    Vector() : Base() { }
    Vector(const Base& v) : Base(v) { }

    T& operator[](int i) { return Base::operator[](i)[0]; }
    const T& operator[](int i) const { return Base::operator[](i)[0]; }
};

template<typename T, int N, int M> struct Affine
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

int main()
{ _
    exit(0);
}
