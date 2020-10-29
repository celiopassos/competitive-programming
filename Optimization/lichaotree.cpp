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

// May define any kind of function,
// as long as intersections are unique.
// Should default to constant = infinity

// E.g., linear function:

template<typename T>
struct Linear
{
    T a = 0, b = numeric_limits<T>::max();
    T operator()(T x) const { return a * x + b; }
};

template<typename Func, typename Domain>
struct LiChaoTree
{
    Domain L, R;
    Func inf = Func();
    vector<Func> st;
    vector<int> LEFT, RIGHT;

    LiChaoTree(Domain L, Domain R) : L(L), R(R) { create(); }

    int create()
    {
        LEFT.push_back(-1), RIGHT.push_back(-1);
        st.push_back(inf);
        return size(st) - 1;
    }
    int left(int p) { return LEFT[p] == -1 ? LEFT[p] = create() : LEFT[p]; }
    int right(int p) { return RIGHT[p] == -1 ? RIGHT[p] = create() : RIGHT[p]; }

    bool is_inf(const Func& f) const
    {
        return f(L) == inf(L) && f(R - 1) == inf(R - 1);
    }
    void update(Func add)
    {
        Domain l = L, r = R; int p = 0;
        while (l < r)
        {
            Domain m = l + (r - l) / 2;
            bool lft = add(l) < st[p](l);
            bool mid = add(m) < st[p](m);
            if (mid) swap(add, st[p]);
            if (r - l == 1 || is_inf(add)) break;
            if (lft != mid) p = left(p), r = m;
            else p = right(p), l = m + 1;
        }
    }
    auto query(Domain x) // returns minimum
    {
        auto res = inf(x);
        Domain l = L, r = R;
        int p = 0;
        while (l < r)
        {
            res = min(res, st[p](x));
            Domain m = l + (r - l) / 2;
            if (m == x || is_inf(st[p])) break;
            else if (x < m) p = left(p), r = m;
            else p = right(p), l = m + 1;
        }
        return res;
    }
    int (size)() const { return size(st); }
};

int main()
{ _
    int n, m; cin >> n >> m;

    vector E(0, tuple(0, 0, 0));

    vector a(m, 0), b(m, 0), s(m, 0), e(m, 0);
    for (int j = 0; j < m; ++j)
    {
        cin >> a[j] >> b[j] >> s[j] >> e[j];

        --a[j], --b[j];

        E.emplace_back(s[j], 0, j);
        E.emplace_back(e[j], 1, j);
    }

    sort(all(E));

    const int tmax = 1e6;

    using F = Linear<ll>;
    vector LCT(n, LiChaoTree<F, int>(0, tmax + 1));

    auto sq = [&](ll x) { return x * x; };

    vector cost(m, LINF);

    LCT[0].update(F{ 0LL, 0LL });

    for (auto [t, type, j] : E)
    {
        if (type == 0)
        {
            auto Q = LCT[a[j]].query(s[j]);
            if (Q < LINF) cost[j] = sq(s[j]) + Q;
        }
        else
        {
            auto Q = cost[j];
            assert(Q >= 0);
            if (Q < LINF) LCT[b[j]].update(F{ -2 * e[j], sq(e[j]) + Q });
        }
    }

    ll ans = LINF;

    for (int j = 0; j < m; ++j)
        if (b[j] == n - 1) ans = min(ans, cost[j]);

    cout << ans << endl;

    exit(0);
}
