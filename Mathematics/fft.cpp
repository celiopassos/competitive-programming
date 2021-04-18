// NTT stuff:
//
// 998244353 = 1 + 7 * 17 * (2 ^ 23)
// 469762049 = 1 + 7 * (2 ^ 26)
// 167772161 = 1 + 5 * (2 ^ 25)

// constexpr int MODs[] = { 998244353, 469762049, 167772161 };
// constexpr int preexp[] = { 7 * 17, 7, 5 };
// constexpr int explog[] = { 23, 26, 25 };
// constexpr int primitive[] = { 3, 3, 3 };

template<typename T>
T getroot(int e) {
    static auto PI = acos(T(-1).real());
    return polar<decltype(PI)>(1, 2 * PI / (1 << e));
}

// using M998 = Mint<MODs[0]>;
// 
// template<>
// M998 getroot<M998>(int e)
// {
//      return M998(primitive[0]).power(preexp[0] * (1LL << (explog[0] - e)));
// }

int logceil(int n) {
    return __builtin_clz(1) - __builtin_clz(n) + !!(n & (n - 1));
}

template<typename T>
void fft(vector<T>& p, vector<T>& aux, T x, int idx, int n) {
    if (n == 1) return;
    int k = n >> 1, ldx = idx, rdx = idx + k;
    for (int i = 0, cur = ldx, nxt = rdx; i < n; ++i, swap(cur, nxt))
        aux[cur + (i >> 1)] = p[idx + i];
    fft(aux, p, x * x, ldx, k), fft(aux, p, x * x, rdx, k);
    for (auto [i, xp] = tuple(0, T(1)); i < n; ++i, xp *= x)
        p[idx + i] = aux[ldx + (i % k)] + xp * aux[rdx + (i % k)];
}

template<typename T>
void fft(vector<T>& p, T root) {
    assert(__builtin_popcountll(size(p)) == 1);
    static vector<T> aux;
    aux.resize(max(size(aux), size(p)));
    fft(p, aux, root, 0, (int)size(p));
}

template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    const int n = (int)size(p), m = (int)size(q);
    const int e = logceil(n + m - 1), N = 1 << e;
    T root = getroot<T>(e);
    p.resize(N, T(0)), q.resize(N, T(0));
    fft(p, root), fft(q, root);
    for (int i = 0; i < N; ++i) p[i] *= q[i];
    fft(p, T(1) / root);
    for (int i = 0; i < N; ++i) p[i] /= T(N);
    p.resize(n + m - 1);
    return p;
}
