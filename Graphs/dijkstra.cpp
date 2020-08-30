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

using ii = pair<int, int>;

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
            auto [u, d] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : E[u])
                if (chmin(dist[v], dist[u] + w))
                    pq.push(pair(dist[v], v));
        }
        return dist;
    };

    exit(0);
}

