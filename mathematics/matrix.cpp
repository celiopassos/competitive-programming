template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> zero(int N, int M) {
  return Matrix<T>(N, std::vector<T>(N));
}

template <typename T>
Matrix<T> zero(int N) {
  return zero<T>(N, N);
}

template <typename T>
Matrix<T> identity(int N) {
  auto I = zero<T>(N);
  for (int i = 0; i < N; ++i) {
    I[i][i] = 1;
  }
  return I;
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
  int N = A.size(), M = A[0].size(), K = B[0].size();
  assert(M == B.size());
  Matrix<T> C(N, std::vector<T>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < K; ++j) {
      for (int k = 0; k < M; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  return C;
}

template <typename T>
std::vector<T> operator*(const Matrix<T>& A, const std::vector<T>& b) {
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
