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

bool chmin(auto& x, auto y)
{
    return y < x ? x = y, true : false;
}

template<typename T>
auto dijkstra(int s, const auto& E)
{
    vector dist(size(E), T(LINF)); dist[s] = T(0);
    struct Data
    {
        T key; int v;
        Data(T key, int v) : key(key), v(v) { }
        bool operator<(const Data& rhs) const { return key > rhs.key; }
    };
    priority_queue<Data> pq; pq.emplace(dist[s], s);
    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : E[u])
            if (chmin(dist[v], dist[u] + w)) pq.emplace(dist[v], v);
    }
    return dist;
}

int main()
{ _
    exit(0);
}

