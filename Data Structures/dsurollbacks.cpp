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

class DSU
{
private:
    vector<int> p, sz;
    stack<pair<int&, int>> snapshots;
    int num_disjoint_sets;
public:
    DSU(const int n) : num_disjoint_sets(n)
    {
        p.assign(n, 0), sz.assign(n, 1);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find_set(int i) const
    {
        while (p[i] != i) i = p[i];
        return i;
    }
    int set_size(int i) const { return sz[find_set(i)]; }
    int num_sets() const { return num_disjoint_sets; }
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
    void union_set(int i, int j)
    {
        int x = find_set(i), y = find_set(j);

        if (sz[x] < sz[y]) swap(x, y);

        save(num_disjoint_sets);
        save(p[y]);
        save(sz[x]);

        if (x != y)
        {
            --num_disjoint_sets;
            p[y] = x;
            sz[x] += sz[y];
        }
    }
};

int main()
{ _
    exit(0);
}
