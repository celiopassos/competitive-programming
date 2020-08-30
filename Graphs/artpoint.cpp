#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

vvi E;
vi dfs_num;
vi dfs_low;
vi dfs_parent;
int dfs_counter = 0, dfs_root = 1, root_children = 0;

const int UNVISITED = 0, VISITED = 1, EXPLORED = 2;

void artpointbridge(int u)
{
    dfs_num[u] = dfs_low[u] = dfs_counter++;

    for (auto v : E[u])
    {
        if (dfs_num[v] == UNVISITED) // tree edge
        {
            dfs_parent[v] = u;

            if (u == dfs_root)
                root_children++;

            artpointbridge(v);

            if (dfs_low[v] >= dfs_num[u])
                cout << u << " is an articulation point\n";

            if (dfs_low[v] > dfs_num[u])
                cout << "{" << u << ", " << v << ") is a bridge\n";

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }

        else if (v != dfs_parent[u]) // back edge
        {
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

