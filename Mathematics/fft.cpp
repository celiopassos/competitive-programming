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
    int N = 1, logN = 0;
    while ((int)size(p) > N) N <<= 1, ++logN;
    p.resize(N);
    for (int i = 0; i < N; ++i) {
        int rev = 0;
        for (int k = 0; k < logN; ++k) {
            rev |= (i >> k & 1) << (logN - 1 - k);
        }
        if (i < rev) swap(p[i], p[rev]);
    }
    vector<T> q(N);
    for (int k = 1; k <= logN; ++k) {
        int len = 1 << k, hlen = len / 2;
        T rt = getroot(len);
        if (inverse) rt = 1 / rt;
        for (int l = 0; l < N; l += len) {
            T x = 1;
            for (int i = 0; i < len; ++i, x *= rt) {
                q[l + i] = p[l + i % hlen] + x * p[l + hlen + i % hlen];
            }
        }
        swap(p, q);
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
