template<typename T>
T determinant(matrix<T> A) {
    int N = (int)size(A);
    assert(N == (int)size(A[0]));
    T det = 1;
    for (int x = 0; x < N; ++x) {
        int sel = -1;
        for (int i = x; i < N; ++i) {
            if (A[i][x] != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) return 0;
        if (sel != x) {
            swap(A[sel], A[x]);
            det *= -1;
        }
        det *= A[x][x];
        for (int i = 0; i < N; ++i) {
            if (i == x) continue;
            T c = A[i][x] / A[x][x];
            for (int j = x; j < N; ++j) {
                A[i][j] -= c * A[x][j];
            }
        }
    }
    return det;
}
