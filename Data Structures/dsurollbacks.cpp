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

class DSU
{
private:
    vector<int> p, sz;
    stack<pair<int&, int>> snapshots;
    int num;
public:
    DSU(const int n) : num(n)
    {
        p.assign(n, 0), sz.assign(n, 1);
        for (int u = 0; u < n; ++u) p[u] = u;
    }
    int find_set(int u) const
    {
        while (p[u] != u) u = p[u];
        return u;
    }
    int getsize(int u) const { return sz[find_set(u)]; }
    int (size)() const { return num; }
    void save(int& x)
    {
        snapshots.push(pair<int&, int>(x, x));
    }
    void rollback()
    {
        for (int t = 0; t < 3; ++t)
        {
            snapshots.top().first = snapshots.top().second;
            snapshots.pop();
        }
    }
    void union_set(int u, int v)
    {
        int x = find_set(u), y = find_set(v);
        if (sz[x] < sz[y]) swap(x, y);
        save(num), save(p[y]), save(sz[x]);
        if (x != y) num -= 1, p[y] = x, sz[x] += sz[y];
    }
};

int main()
{ _
    exit(0);
}
