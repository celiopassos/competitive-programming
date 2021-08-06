template<typename T>
using matrix = vector<vector<T>>;
template<typename T>
matrix<T> operator*(const matrix<T>& A, const matrix<T>& B) {
    int N = (int)A.size(), M = (int)A[0].size(), K = (int)B[0].size();
    assert(M == (int)B.size());
    matrix<T> C(N, vector<T>(M));
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
vector<T> operator*(const matrix<T>& A, const vector<T>& b) {
    int N = (int)A.size(), M = (int)A[0].size();
    assert(M == (int)b.size());
    vector<T> y(N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            y[i] += A[i][j] * b[j];
        }
    }
    return y;
}
