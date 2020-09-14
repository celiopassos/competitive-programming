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

template<typename T, int... Args>
struct SegmentTree
{
    static const T id = T();
    static T combine(T x, T y) { return x + y; }
    T value = id;
    void update(T add) { value = combine(value, add); }
    T query() { return value; }
};

template<typename T, int N, int... Ns>
struct SegmentTree<T, N, Ns...>
{
private:
    using ST = SegmentTree<T>;
    array<SegmentTree<T, Ns...>, 2 * N> st;
public:
    template<typename... Args>
    void update(int p, Args... args)
    {
        for (p += N; p; p >>= 1) st[p].update(args...);
    }
    template<typename... Args>
    T query(int l, int r, Args... args)
    {
        T resl = ST::id, resr = ST::id;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1) resl = ST::combine(resl, st[l++].query(args...));
            if (r & 1) resr = ST::combine(st[--r].query(args...), resr);
        }
        return ST::combine(resl, resr);
    }
};

int main()
{ _
    exit(0);
}
