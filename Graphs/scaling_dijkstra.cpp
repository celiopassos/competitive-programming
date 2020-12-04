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

bool chmin(auto& x, auto y) { return y < x ? x = y, true : false; }

template<typename T>
auto dijkstra(int s, const auto& E)
{
    const int n = size(E);

    int logmax = 0;
    for (int u = 0; u < n; ++u)
        for (auto [v, w] : E[u])
            logmax = max(logmax, __builtin_clzll(1LL) - __builtin_clzll(w));

    vector<T> pi(n, 0), dist(n, 0), d(n, 0);
    vector<vector<int>> bucket(n);

    for (int i = logmax; i >= 0; --i)
    {
        for (int u = 0; u < n; ++u)
            pi[u] = dist[u] << 1, d[u] = n;
        bucket[d[s] = 0].push_back(s);

        for (int k = 0; k < n; ++k)
            while (not bucket[k].empty())
            {
                int u = bucket[k].back(); bucket[k].pop_back();
                if (d[u] < k) continue;
                for (auto [v, w] : E[u])
                    if (chmin(d[v], d[u] + pi[u] - pi[v] + (w >> i)))
                    {
                        bucket[d[v]].push_back(v);
                        dist[v] = dist[u] + (w >> i);
                    }
            }
    }
    return dist;
}

int main()
{ _
    exit(0);
}
