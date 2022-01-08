template<typename T>
using matrix = std::vector<std::vector<T>>;
template<typename T>
matrix<T> zero(int N, int M) {
    return matrix<T>(N, std::vector<T>(N));
}
template<typename T>
matrix<T> zero(int N) {
    return zero<T>(N, N);
}
template<typename T>
matrix<T> identity(int N) {
    auto I = zero<T>(N);
    for (int i = 0; i < N; ++i) {
        I[i][i] = 1;
    }
    return I;
}
template<typename T>
matrix<T> operator*(const matrix<T>& A, const matrix<T>& B) {
    int N = A.size(), M = A[0].size(), K = B[0].size();
    assert(M == B.size());
    matrix<T> C(N, std::vector<T>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < K; ++j) {
            for (int k = 0; k < M; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
template<typename T>
std::vector<T> operator*(const matrix<T>& A, const std::vector<T>& b) {
    int N = A.size(), M = A[0].size();
    assert(M == b.size());
    std::vector<T> y(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            y[i] += A[i][j] * b[j];
        }
    }
    return y;
}
