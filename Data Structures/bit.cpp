#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

struct F1
{
    static auto op(const auto& x, const auto& y) { return x + y; }
    static auto inv(const auto& x) { return -x; }
};

template<typename T, typename F>
class BIT
{
private:
    int b(int p) { return p & (-p); }
    const int n; const T id;
    vector<T> ft;
    T query(int p)
    {
        T res = id;
        for (int i = p; i >= 1; i -= b(i)) res = F::op(ft[i], res);
        return res;
    }
public:
    BIT(int n, T id) : n(n), id(id) { ft.assign(n + 1, id); }
    BIT(const vector<T>& a, T id) : BIT(sz(a), id)
    {
        for (int i = 1; i <= n; ++i) ft[i] = F::op(ft[i - 1], a[i - 1]);
        for (int i = n; i >= 1; --i) ft[i] = F::op(F::inv(ft[i - b(i)]), ft[i]);
    }
    T query(int l, int r) { return F::op(F::inv(query(l)), query(r + 1)); }
    void update(int p, T value)
    {
        for (int i = p + 1; i <= n; i += b(i)) ft[i] = F::op(ft[i], value);
    }
};

int main()
{ _
    exit(0);
}

