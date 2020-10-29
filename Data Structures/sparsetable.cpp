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
class SparseTable
{
private:
    const int n;
    const function<T(T, T)> op;
    vector<int> log;
    vector<vector<T>> st;
public:
    SparseTable(const vector<T>& a, const function<T(T, T)> op) : n(size(a)), op(op)
    {
        log.assign(n + 1, 0);
        for (int x = 1; x <= n; ++x) log[x] = 31 - __builtin_clz(x);
        st.assign(n, vector<T>(log[n] + 1, T()));
        for (int i = 0; i < n; ++i) st[i][0] = a[i];
        for (int x = 1; x <= log[n]; ++x)
            for (int i = 0; i + (1 << x) <= n; ++i)
                st[i][x] = op(st[i][x - 1], st[i + (1 << (x - 1))][x - 1]);
    }
    T query(int l, int r)
    {
        int x = log[r - l + 1];
        return op(st[l][x], st[r - (1 << x) + 1][x]);
    }
};

int main()
{ _
    exit(0);
}

