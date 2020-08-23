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

class LCA
{
private:
    const vector<vector<int>>& E;
    const int n, lg;
    vector<int> L, R, h;
    vector<vector<int>> up;
    void dfs(int u, int p)
    {
        h[u] = h[p] + 1, up[u][0] = p;
        for (int i = 1; i < lg; ++i)
            up[u][i] = up[up[u][i-1]][i-1];
        static int ct = 0;
        L[u] = ct;
        for (int v : E[u])
            if (v != p) dfs(v, u);
        R[u] = ct++;
    }
public:
    LCA(const vector<vector<int>>& E, int root) : E(E), n(sz(E)), lg(32 - __builtin_clz(n))
    {
        L.assign(n, 0), R.assign(n, 0), h.assign(n, -1);
        up.assign(n, vector<int>(lg));
        dfs(root, root);
    }
    bool is_ancestor(int u, int v) const
    {
        return L[u] <= L[v] && R[v] <= R[u];
    }
    int lca(int u, int v) const
    {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = lg - 1; i >= 0; --i)
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    }
    int distance(int u, int v) const
    {
        int w = lca(u, v);
        return h[u] + h[v] - 2 * h[w];
    }
};

int main()
{ _
    exit(0);
}

