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

template<typename T>
struct F1
{
    const T id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static T inv(const T& x) { return -x; }
};

template<typename T, typename F>
class BIT
{
private:
    int b(int p) { return p & (-p); }
    const int n;
    vector<T> ft;
    T query(int p)
    {
        T res = F::id;
        for (int i = p; i >= 1; i -= b(i)) res = F::op(ft[i], res);
        return res;
    }
public:
    BIT(int n) : n(n) { ft.assign(n + 1, F::id); }
    BIT(const vector<T>& a) : BIT(size(a), F::id)
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

