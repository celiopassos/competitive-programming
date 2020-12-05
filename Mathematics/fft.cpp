#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// Primes for NTT
// 998244353 = 1 + 7 * 17 * (2 ^ 23)
// 469762049 = 1 + 7 * (2 ^ 26)
// 167772161 = 1 + 5 * (2 ^ 25)

constexpr int MODs[] = { 998244353, 469762049, 167772161 };
constexpr int preexp[] = { 7 * 17, 7, 5 };
constexpr int explog[] = { 23, 26, 25 };
constexpr int primitive[] = { 3, 3, 3 };

template<int idx>
constexpr auto getroot(int e)
{
    using M = Mint<MODs[idx]>;
    return M(primitive[idx]).power(preexp[idx] * (1LL << (explog[idx] - e)));
}

int logceil(int n)
{
    return __builtin_clz(1) - __builtin_clz(n) + !!(n & (n - 1));
}

template<typename T>
void fft(vector<T>& p, vector<T>& aux, T x, int idx, int n)
{
    if (n == 1) return;

    int k = n >> 1, ldx = idx, rdx = idx + k;

    for (int i = 0, cur = ldx, nxt = rdx; i < n; ++i, swap(cur, nxt))
        aux[cur + (i >> 1)] = p[idx + i];

    fft(aux, p, x * x, ldx, k), fft(aux, p, x * x, rdx, k);

    for (auto [i, xp] = tuple(0, T(1)); i < n; ++i, xp *= x)
        p[idx + i] = aux[ldx + (i % k)] + xp * aux[rdx + (i % k)];
}

template<typename T>
void fft(vector<T>& p, T root)
{
    assert(__builtin_popcount(size(p)) == 1);
    static vector<T> aux;
    aux.resize(max(size(aux), size(p)));
    fft(p, aux, root, 0, size(p));
}

// rootbuilder should accept an integer e as input
// and return a (1 << e)-th root of unity

template<typename T>
vector<T> convolution(vector<T> p, vector<T> q, auto rootbuilder)
{
    const int n = size(p), m = size(q);
    const int e = logceil(n + m - 1), N = 1 << e;

    T root = rootbuilder(e);

    p.resize(N, T(0)), q.resize(N, T(0));

    fft(p, root), fft(q, root);
    for (int i = 0; i < N; ++i) p[i] *= q[i];

    fft(p, T(1) / root);
    for (int i = 0; i < N; ++i) p[i] /= T(N);

    p.resize(n + m - 1);

    return p;
}

int main()
{ _
    exit(0);
}
