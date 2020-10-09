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
    vector<int> p, rk, sz;
    int num_disjoint_sets;
public:
    DSU(int n) : num_disjoint_sets(n)
    {
        rk.assign(n, 0), p.assign(n, 0), sz.assign(n, 1);
        for (int i = 0; i < n; ++i) p[i] = i;
    }
    int find_set(int i) { return p[i] == i ? i : p[i] = findset(p[i]); }
    int set_size(int i) { return sz[find_set(i)]; }
    int num_sets() { return num_disjoint_sets; }
    void union_set(int i, int j)
    {
        int x = find_set(i), y = find_set(j);
        if (rk[x] < rk[y]) swap(x, y);
        if (x != y)
        {
            --num_disjoint_sets;
            p[y] = x;
            rk[x] += (rk[x] == rk[y]);
            sz[x] += sz[y];
        }
    }
};

int main()
{ _
    exit(0);
}
