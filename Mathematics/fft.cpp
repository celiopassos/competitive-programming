template<typename T>
complex<T> getroot(int N) {
    static const double PI = acos(-1);
    return polar<T>(1, 2 * PI / N);
}
//Mint<998244353> getroot(int N) {
//     return Mint<998244353>(3).power(7 * 17 * (1LL << 23) / N);
//}
// inplace fft (resizes if necessary)
template<typename T>
void fft(vector<T>& p, bool inverse) {
    int N = 1;
    while ((int)size(p) > N) N *= 2;
    static vector<T> q;
    p.resize(N), q.resize(N);
    for (int len = N; len > 1; len /= 2, swap(p, q)) {
        for (int l = 0; l < N; l += len) {
            int c[2] = {l, l + len / 2};
            for (int i = 0; i < len; ++i) {
                q[c[i % 2] + i / 2] = p[l + i];
            }
        }
    }
    for (int len = 2, hlen = 1; len <= N; len *= 2, hlen *= 2, swap(p, q)) {
        T rt = inverse ? getroot(len) : 1 / getroot(len);
        for (int l = 0; l < N; l += len) {
            for (auto [i, x] = pair(0, T(1)); i < len; ++i, x *= rt) {
                q[l + i] = p[l + i % hlen] + x * p[l + hlen + i % hlen];
            }
        }
    }
    if (inverse) {
        T inv = 1 / T(N);
        for (int i = 0; i < N; ++i) p[i] *= inv;
    }
}
template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    size_t N = size(p) + size(q) - 1;
    p.resize(N), q.resize(N);
    fft(p, false), fft(q, false);
    for (size_t i = 0; i < size(p); ++i) p[i] *= q[i];
    fft(p, true);
    p.resize(N);
    return p;
}
