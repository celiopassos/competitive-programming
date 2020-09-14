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

template <typename T, int... Args>
struct BIT
{
    static const T id = T();
    static T combine(T x, T y) { return x + y; }
    static T inv(T x) { return -x; }
    T value = id;
    void update(T nw) { value = combine(value, nw); }
    int query() { return value; }
};

template <typename T, int N, int... Ns>
class BIT<T, N, Ns...>
{
private:
    using B = BIT<T>;
    array<BIT<T, Ns...>, N> ft;
    template<typename... Args>
    T prefix(int p, Args... args)
    {
        T res = B::id;
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1)
            res = B::combine(res, ft[i].query(args...));
        return res;
    }
public:
    template<typename... Args>
    void update(int p, Args... args)
    {
        for (int i = p; i <= N; i = i | (i + 1))
            ft[i].update(args...);
    }
    template<typename... Args>
    T query(int l, int r, Args... args)
    {
        if (l == 0) return prefix(r, args...);
        return B::combine(B::inv(prefix(l - 1, args...)), prefix(r, args...));
    }
};

void solve()
{
    int n; cin >> n;
    constexpr int N = 1024;

    BIT<int, N, N> bit;

    for (string q; (cin >> q) && q != "END";)
    {
        if (q == "SET")
        {
            int x, y, num; cin >> x >> y >> num;
            bit.update(x, y, num - bit.query(x, x, y, y));
        }
        else
        {
            int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
            int ans = bit.query(x1, x2, y1, y2);
            cout << ans << endl;
        }
    }
    cout << endl;
}

int main()
{ _
    int t; cin >> t;
    while (t--) solve();
    exit(0);
}
