template<typename T>
T getroot(int N) {
    static auto PI = acos(T(-1).real());
    return polar<decltype(PI)>(1, 2 * PI / N);
}

template<typename T>
void fft(vector<T>& p, vector<T>& aux, T rt, int idx, int n) {
    if (n == 1) return;
    int k = n >> 1, ldx = idx, rdx = idx + k;
    for (int i = 0, cur = ldx, nxt = rdx; i < n; ++i, swap(cur, nxt))
        aux[cur + (i >> 1)] = p[idx + i];
    fft(aux, p, rt * rt, ldx, k), fft(aux, p, rt * rt, rdx, k);
    for (auto [i, xp] = pair(0, T(1)); i < n; ++i, xp *= rt)
        p[idx + i] = aux[ldx + (i % k)] + xp * aux[rdx + (i % k)];
}

// inplace fft, resizes if necessary
template<typename T>
void fft(vector<T>& p, bool inverse = false) {
    int N = 1;
    while ((int)size(p) > N) N <<= 1;
    p.resize(N);
    static vector<T> aux;
    aux.resize(max(size(aux), size(p)));
    T root = getroot<T>(N);
    if (inverse) {
        fft(p, aux, T(1) / root, 0, N);
        T inv = T(1) / T(N);
        for (int i = 0; i < N; ++i) p[i] *= inv;
    }
    else fft(p, aux, root, 0, N);
}

template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    int n = (int)size(p), m = (int)size(q), N = n + m - 1;
    p.resize(N), q.resize(N);
    fft(p), fft(q);
    for (size_t i = 0; i < size(p); ++i) p[i] *= q[i];
    fft(p, true);
    p.resize(N);
    return p;
}
