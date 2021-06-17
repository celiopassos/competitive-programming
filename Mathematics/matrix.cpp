template<typename T, int N, int M>
struct Matrix : public array<array<T, M>, N> {
    Matrix(T diag = T()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                (*this)[i][j] = (i == j ? diag : T());
            }
        }
    }
    Matrix(initializer_list<initializer_list<T>> lst) : Matrix() {
        int i = 0, j = 0;
        for (auto& v : lst) {
            for (auto x : v) (*this)[i][j++] = x;
            i++, j = 0;
        }
    }
    template<typename Op> Matrix& compose(const Matrix& rhs, Op&& op) {
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
    template<int K> Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const {
        const auto& lhs = *this;
        Matrix<T, N, K> res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < K; ++j)
                for (int k = 0; k < M; ++k)
                    res[i][j] += lhs[i][k] * rhs[k][j];
        return res;
    }
    Matrix power(ll p) {
        Matrix res(1), A = *this;
        while (p) {
            if (p & 1) res = A * res;
            A *= A, p >>= 1;
        }
        return res;
    }
    friend Matrix operator*(const T& alpha, Matrix A) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] *= alpha;
        return A;
    }
};
template<typename T, int N>
struct Vector : public Matrix<T, N, 1> {
    using Base = Matrix<T, N, 1>;
    Vector() : Base() { }
    Vector(const Base& v) : Base(v) { }
    Vector(initializer_list<T> lst) : Base() {
        int i = 0;
        for (const auto& x : lst) (*this)[i++] = x;
    }
    T& operator[](int i) { return Base::operator[](i)[0]; }
    const T& operator[](int i) const { return Base::operator[](i)[0]; }
};
template<typename T, int N, int M>
struct Affine {
    Matrix<T, N, M> A;
    Vector<T, N> b;
    Affine(T value = T(0)) : A(value) { }
    Affine(const Matrix<T, N, M>& A, const Vector<T, N>& b) : A(A), b(b) { }
    Affine operator+=(const Affine& rhs) { A += rhs.A, b += rhs.B; }
    Affine operator-=(const Affine& rhs) { A -= rhs.A, b -= rhs.B; }
    Affine operator+(const Affine& rhs) const { return Affine(*this) += rhs; };
    Affine operator-(const Affine& rhs) const { return Affine(*this) -= rhs; };
    T* operator[](int i) { return A[i]; }
    const T* operator[](int i) const { return A[i]; }
    template<int K> Affine<T, N, K> operator*(const Affine<T, M, K>& rhs) const {
        return Affine<T, N, K>(A * rhs.A, A * rhs.b + b);
    }
    Vector<T, N> operator*(const Vector<T, M>& x) const {
        return A * x + b;
    }
};
