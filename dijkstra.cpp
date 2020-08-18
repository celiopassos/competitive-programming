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

int main()
{ _
    int n, m; cin >> n >> m;
    vvii E(n);
    for (int j = 0; j < m; ++j)
    {
        int u, v, w; cin >> u >> v >> w; --u, --v;
        E[u].pb(mp(v, w)), E[v].pb(mp(u, w));
    }

    int s = 0;
    vi dist(n, INF); dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> pq; pq.push(mp(0, s));

    while (!pq.empty())
    {
        ii front = pq.top(); pq.pop();
        int d = front.f, u = front.s;

        if (d > dist[u])
            continue;

        for (auto [v, w] : E[u])
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push(mp(dist[v], v));
            }
    }

    exit(0);
}

