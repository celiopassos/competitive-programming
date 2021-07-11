template<typename T, int N>
struct Combinatorics {
    Combinatorics() = delete;
    inline static T f[N], inv[N];
    static void build() {
        f[0] = inv[0] = 1;
        for (int x = 1; x < N; ++x) f[x] = x * f[x - 1], inv[x] = 1 / f[x];
    }
    static T interpolate(const vector<T>& y, T x) {
        static T pref[N], suff[N];
        int n = (int)size(y);
        pref[0] = suff[n - 1] = 1;
        for (int i = 0; i + 1 < n; ++i) pref[i + 1] = pref[i] * (x - i);
        for (int i = n - 1; i > 0; --i) suff[i - 1] = suff[i] * (x - i);
        T res = 0;
        for (int i = 0, sgn = (n % 2 ? +1 : -1); i < n; ++i, sgn *= -1) {
            res += y[i] * sgn * pref[i] * suff[i] * inv[i] * inv[n - 1 - i];
        }
        return res;
    }
    static T C(int n, int k) {
        return k < 0 || n < k ? 0 : f[n] * inv[k] * inv[n - k];
    }
    static T S(int n, int k) {
        return k == 0 ? n == 0 : C(n + k - 1, k - 1);
    }
};
