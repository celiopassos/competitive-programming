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

template<typename T>
T safemod(T a, T mod)
{
    return (a %= mod) < 0 ? a + mod : a;
}

template<typename T>
T safeprod(T a, T b, T mod)
{
    T res = T(0);

    for (a = safemod(a, mod), b = safemod(b, mod); a > 0; a >>= 1, b = (b + b) % mod)
        if (a & 1) res = (res + b) % mod;

    return res;
}

template<typename T>
auto invgcd(T a, T b)
{
    if ((a = safemod(a, b)) == 0) return pair(b, T(0));
    T s = b, t = a, x = 0, y = 1;
    while (t > 0)
    {
        T q = s / t;
        s -= t * q, x -= y * q;
        swap(s, t), swap(x, y);
    }
    if (x < 0) x += b / s;
    return pair(s, x);
}

template<typename T>
auto extended_euclidean(T a, T b)
{
    auto [g, x] = invgcd(a, b);
    T y = (g - x * a) / b;
    return tuple(x, y, g);
}

template<typename T>
auto chinese_remainder(const vector<pair<T, T>>& eq)
{
    T acur = T(0), modcur = T(1);

    for (auto [a, mod] : eq)
    {
        a = safemod(a, mod);

        if (modcur < mod) swap(acur, a), swap(modcur, mod);

        auto [x, y, g] = extended_euclidean(modcur, mod);

        if (safemod(acur - a, g) != T(0)) return pair(T(-1), T(-1));

        T modnxt = modcur * (mod / g);

        acur = acur + safeprod((a - acur) / g, safeprod(x, modcur, modnxt), modnxt);

        acur %= modnxt, modcur = modnxt;
    }

    return pair(acur, modcur);
}

int main()
{ _
    exit(0);
}
