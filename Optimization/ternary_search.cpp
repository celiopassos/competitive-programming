#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

template<typename F, typename T>
pair<F, T> ternary_search(T l, T r, function<F(T)>& f)
{
    const T eps = 2;
    while (r - l > eps)
    {
        T m1 = l + (r - l) / 3;
        T m2 = r - (r - l) / 3;
        if (f(m1) < f(m2)) l = m1;
        else r = m2;
    }
    T c = l;
    for (T x = c + 1; x <= r; ++x)
        if (f(x) > f(c)) c = x;
    return { f(c), c }; // maximum
}

int main()
{ _
    int n = 10;
    auto f = [&](int x) { return n * x * (10 - x); };
    int x = ternary_search<int, int>(0, 10, f).first;
    debug(x);
    exit(0);
}

