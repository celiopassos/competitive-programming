#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

int main()
{ _
    int n, m; cin >> n >> m;
    vector E(n, vector(0, pair(0, 0)));
    for (int j = 0; j < m; ++j)
    {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        E[u].push_back(pair(v, w)), E[v].push_back(pair(u, w));
    }

    auto chmin = [&](int& x, int y) { return y < x ? x = y, true : false; };
    auto dijkstra = [&](int s)
    {
        vector dist(n, INF); dist[s] = 0;
        priority_queue<ii, vector<ii>, greater<ii>> pq; pq.push(pair(0, s));
        while (!pq.empty())
        {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : E[u])
                if (chmin(dist[v], dist[u] + w))
                    pq.push(pair(dist[v], v));
        }
        return dist;
    };

    exit(0);
}

