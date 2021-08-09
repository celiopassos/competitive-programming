template<typename T>
complex<T> root_of_unity(int N, complex<T> dummy) {
    return polar<T>(1, 2 * acos(-1) / N);
}
//template<long long P>
//Z<P> root_of_unity(int N, Z<P> dummy) {
//    return Z<P>(3).power((P - 1) / N);
//}
template<typename T>
vector<T> fft(vector<T> p, bool inverse) {
    int N = (int)p.size();
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
        T w = root_of_unity(b << 1, T());
        if (inverse) w = T(1) / w;
        for (auto [i, x] = pair(0, T(1)); i < N; ++i, x *= w) {
            q[i] = p[i & ~b] + x * p[i | b];
        }
        swap(p, q);
    }
    if (inverse) {
        T inv = T(1) / T(N);
        for (int i = 0; i < N; ++i) p[i] *= inv;
    }
    return p;
}
template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    int N = int(p.size() + q.size() - 1), M = 1;
    while (M < N) M <<= 1;
    p.resize(M), q.resize(M);
    auto phat = fft(p, false), qhat = fft(q, false);
    for (int i = 0; i < M; ++i) {
        phat[i] *= qhat[i];
    }
    auto r = fft(phat, true);
    r.resize(N);
    return r;
}
