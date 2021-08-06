template<typename T>
complex<T> get_root(int N) {
    return polar<T>(1, 2 * acos(-1) / N);
}
//Mint<998244353> get_root(int N) {
//     return Mint<998244353>(3).power(7 * 17 * (1LL << 23) / N);
//}
// inplace fft (resizes if necessary)
template<typename T>
void fft(vector<T>& p, bool inverse) {
    int N = 1;
    while ((int)p.size() > N) N *= 2;
    p.resize(N);
    vector<T> q(N);
    for (int i = 0; i < N; ++i) {
        int rev = 0;
        for (int b = 1; b < N; b <<= 1) {
            rev = (rev << 1) | !!(i & b);
        }
        q[rev] = p[i];
    }
    swap(p, q);
    for (int b = 1; b < N; b <<= 1) {
        T rt = inverse ? 1 / get_root(b << 1) : get_root(b << 1);
        for (auto [i, x] = pair<int, T>(0, 1); i < N; ++i, x *= rt) {
            q[i] = p[i & ~b] + x * p[i | b];
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
    size_t N = p.size() + q.size() - 1;
    p.resize(N), q.resize(N);
    fft(p, false), fft(q, false);
    for (size_t i = 0; i < p.size(); ++i) {
        p[i] *= q[i];
    }
    fft(p, true);
    p.resize(N);
    return p;
}
