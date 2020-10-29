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

int kuhn(int n, int m, const auto& E)
{
    vector<int> matchA(n, -1), matchB(m, -1), vis(m, 0);
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
    int ct = 0;
    while (true)
    {
        fill(all(vis), 0);
        bool aux = false;
        for (int u = 0; u < n; ++u)
            if (matchA[u] == -1 && augment(u)) ct += (aux = true);
        if (not aux) break;
    }
    return ct;
}

int main()
{ _
    exit(0);
}
