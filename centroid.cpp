#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

class CentroidDecomposition
{
private:
    vector<set<int>> E;
    vector<int> par, subsz, level;
    vector<vector<int>> dist;
    int dfs(int u, int p, int h)
    {
        if (h != -1) dist[u][h] = dist[p][h] + 1;
        subsz[u] = 1;
        for (auto v : E[u])
            if (v != p) subsz[u] += dfs(v, u, h);
        return subsz[u];
    }
    int find_centroid(int u, int p, int sz)
    {
        for (auto v : E[u])
            if (v != p && subsz[v] > sz / 2)
                return find_centroid(v, u, sz);
        return u;
    }
    void build(int u, int p)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p;
        if (p != -1) level[centroid] = level[p] + 1;
        for (auto v : E[centroid])
            E[v].erase(centroid), build(v, centroid);
    }
public:
    CentroidDecomposition(const vector<set<int>>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1), subsz.assign(n, 0);
        level.assign(n, 0), dist.assign(n, vector(32 - __builtin_clz(n), 0));
        build(0, -1);
    }
    int operator[](int u) const { return par[u]; }
    int lca(int u, int v) // centroid lca, not tree lca
    {
        if (level[u] < level[v]) swap(u, v);
        while (level[u] > level[v]) u = par[u];
        while (u != v) u = par[u], v = par[v];
        return u;
    }
    int distance(int u, int v)
    {
        int w = lca(u, v);
        return dist[u][level[w]] + dist[v][level[w]];
    }
};

int main()
{ _
    int n; cin >> n;
    vector<set<int>> E(n);
    for (int j = 0; j < n - 1; ++j)
    {
        int u, v; cin >> u >> v; --u, --v;
        E[u].insert(v), E[v].insert(u);
    }
    CentroidDecomposition cd(E);
    exit(0);
}
