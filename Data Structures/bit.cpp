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

template<typename T>
class BIT
{
private:
    T op(T x, T y) { return x + y; }
    T inv(T x) { return -x; }
    int b(int p) { return p & (-p); }
    const int n; const T id;
    vector<T> ft;
    T query(int p)
    {
        T res = id;
        for (int i = p; i >= 1; i -= b(i)) res = op(ft[i], res);
        return res;
    }
public:
    BIT(const vector<T>& a, T id) : n(sz(a)), id(id)
    {
        ft.assign(n + 1, id);
        for (int i = 1; i <= n; ++i) ft[i] = op(ft[i - 1], a[i - 1]);
        for (int i = n; i >= 1; --i) ft[i] = op(inv(ft[i - b(i)]), ft[i]);
    }
    T query(int l, int r) { return op(inv(query(l)), query(r + 1)); }
    void update(int p, T value)
    {
        for (int i = p + 1; i <= n; i += b(i)) ft[i] = op(ft[i], value);
    }
};

int main()
{ _
    exit(0);
}

