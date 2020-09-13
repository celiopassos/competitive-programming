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
{ _
    int n = 0; // n vertices
    vector<vii> E; // (weight, edge)
    // Read into E
    sort(E.begin(), E.end());

    vi visited(n + 1, false);
    priority_queue<ii> pq;
    for (auto [v, w] : E[1])
        pq.push({w, v});
    visited[1] = true;

    int mst_cost = 0;
    while (not pq.empty())
    {
        ii p = pq.top(); pq.pop();
        if (not visited[p.s])
        {
            mst_cost += p.f;

            for (auto [v, w] : E[p.s])
                if (not visited[v])
                    pq.push({w, v});
        }
    }

    exit(0);
}

