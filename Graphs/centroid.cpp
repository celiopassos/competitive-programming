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

class CentroidDecomposition
{
private:
    const vector<vector<int>>& E;
    vector<int> par, subsz, level, vis;
    vector<vector<int>> dist;
    int dfs(int u, int p, int h)
    {
        if (h != -1) dist[u][h] = dist[p][h] + 1;
        subsz[u] = 1;
        for (auto v : E[u])
            if (not vis[v] && v != p) subsz[u] += dfs(v, u, h);
        return subsz[u];
    }
    int find_centroid(int u, int p, int sz)
    {
        for (auto v : E[u])
            if (not vis[v] && v != p && subsz[v] > sz / 2)
                return find_centroid(v, u, sz);
        return u;
    }
    void build(int u, int p)
    {
        int sz = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, sz);
        par[centroid] = p, vis[centroid] = 1;
        if (p != -1) level[centroid] = level[p] + 1;
        for (auto v : E[centroid])
            if (not vis[v]) build(v, centroid);
    }
public:
    CentroidDecomposition(const vector<vector<int>>& E) : E(E)
    {
        int n = size(E);
        par.assign(n, -1), subsz.assign(n, 0), vis.assign(n, 0);
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
    int n, q; cin >> n >> q;
    vector<vector<int>> E(n);
    for (int j = 0; j < n - 1; ++j)
    {
        int u, v; cin >> u >> v; --u, --v;
        E[u].push_back(v), E[v].push_back(u);
    }
    CentroidDecomposition cd(E);
    exit(0);
}

