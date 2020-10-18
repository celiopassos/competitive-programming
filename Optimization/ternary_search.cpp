#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

auto ternary_search(auto l, auto r, auto&& f, auto EPS)
{
    using T = decltype(l);
    while (r - l > EPS)
    {
        T m1 = l + (r - l) / 3;
        T m2 = r - (r - l) / 3;
        if (f(m1) > f(m2)) l = m1;
        else r = m2;
    }
    T c = l;
    for (T x = c + 1; x <= r; ++x) if (f(x) < f(c)) c = x;
    return pair(f(c), c);
}

int main()
{ _
    exit(0);
}

