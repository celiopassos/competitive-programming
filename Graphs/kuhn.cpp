#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

auto kuhn(int n, int m, const auto& E)
{
    vector matchA(n, -1), matchB(m, -1), vis(m, 0);

    function<bool(int)> augment = [&](int u)
    {
        for (auto v : E[u])
        {
            if (vis[v]++) continue;
            if (matchB[v] == -1 || augment(matchB[v]))
            {
                matchA[u] = v, matchB[v] = u;
                return true;
            }
        }
        return false;
    };

    while (true)
    {
        vis.assign(m, 0);
        bool aux = false;
        for (int u = 0; u < n; ++u)
            if (matchA[u] == -1) aux = aux || augment(u);
        if (not aux) break;
    }
    return matchA;
}

int main()
{ _
    exit(0);
}

