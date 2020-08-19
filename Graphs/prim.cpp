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

