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
vi dfs_num, dfs_low, S, visited;
int dfs_counter = 0;

const int UNVISITED = -1;

void tarjanSCC(int u)
{
    dfs_low[u] = dfs_num[u] = dfs_counter++;
    S.push_back(u);
    visited[u] = 1;

    for (auto v : E[u])
    {
        if (dfs_num[v] == UNVISITED)
            tarjanSCC(v);

        if (visited[v]) // if v is part of current SCC
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u])
    {
        cout << "SCC:";
        while (1)
        {
            int v = S.back(); S.pop_back();
            visited[v] = 0;
            cout << " " << v;
            if (u == v) break;
        }
    }
}

int main()
{
    int n = 10;
    dfs_num.assign(n + 1, UNVISITED);
    dfs_low.assign(n + 1, 0);
    visited.assign(n + 1, 0);
    dfs_counter = 0;
    tarjanSCC(1);
}

