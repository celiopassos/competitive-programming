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

template<typename T, typename... Args>
auto ternary_search(T l, T r, T eps, auto&& f, Args... args)
{
    while (r - l > eps)
    {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1, args...) > f(m2, args...)) l = m1;
        else r = m2;
    }
    T c = l;
    for (T x = c + 1; x <= r; ++x)
        if (f(x, args...) < f(c, args...)) c = x;
    return pair(f(c, args...), c);
}

int main()
{ _
    exit(0);
}
