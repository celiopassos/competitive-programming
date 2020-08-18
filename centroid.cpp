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
    vector<int> par, subsz;
    int dfs(int u, int p)
    {
        subsz[u] = 1;
        for (auto v : E[u])
            if (v != p) subsz[u] += dfs(v, u);
        return subsz[u];
    }
    int dfs(int u, int p, int sz)
    {
        for (auto v : E[u])
            if (v != p && subsz[v] > sz / 2)
                return dfs(v, u, sz);
        return u;
    }
    void build(int u, int p)
    {
        int sz = dfs(u, p);
        int centroid = dfs(u, p, sz);
        par[centroid] = p;
        for (auto v : E[centroid])
            E[v].erase(centroid), build(v, centroid);
    }
public:
    CentroidDecomposition(const vector<set<int>>& E) : E(E)
    {
        int n = sz(E);
        par.assign(n, -1), subsz.assign(n, 0);
        build(0, -1);
    }
    int operator[](int u) { return par[u]; }
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

