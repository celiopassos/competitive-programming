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

int main()
{ _
    int n, m; cin >> n >> m;

    int logmax = 0;
    vector E(n, vector(0, pair(0, 0)));
    for (int j = 0; j < m; ++j)
    {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        E[u].push_back(pair(v, w)), E[v].push_back(pair(u, w));
        logmax = max(logmax, 31 - __builtin_clz(w));
    }

    vector p(n, 0), dist(n, 0), d(n, 0);
    vector<vector<int>> bucket(n - 1);

    auto chmin = [](auto& x, auto y){ return y < x ? x = y, true : false; };

    auto dial = [&](int s, int i)
    {
        for (int u = 0; u < n; ++u)
            p[u] = dist[u] << 1, d[u] = n - 1;
        bucket[d[s] = 0].push_back(s);

        for (int k = 0; k < n - 1; ++k)
            while (not bucket[k].empty())
            {
                int u = bucket[k].back(); bucket[k].pop_back();
                if (d[u] < k) continue;
                for (auto [v, w] : E[u])
                    if (chmin(d[v], d[u] + p[u] - p[v] + (w >> i)))
                    {
                        bucket[d[v]].push_back(v);
                        dist[v] = dist[u] + (w >> i);
                    }
            }
    };

    int s = 0;
    for (int i = logmax; i >= 0; --i) dial(s, i);

    exit(0);

}

