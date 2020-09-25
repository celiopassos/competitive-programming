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

auto chmin(auto& x, auto y) { return y < x ? x = y, true : false; }

template<typename Cap, typename Cost>
struct MCMF
{
    struct Edge
    {
        int from, to;
        Cap cap, flow = 0;
        Cost cost;
        Edge(int u, int v, Cap cap, Cost cost) :
            from(u), to(v), cap(cap), cost(cost) {}
        Cap free() const { return cap - flow; }
    };
    const int n;
    const Cap infcap = numeric_limits<Cap>::max();
    const Cost infcost = numeric_limits<Cost>::max();
    vector<Edge> edges;
    vector<vector<int>> E;

    MCMF(int n) : n(n) { E.resize(n); }

    int m = 0;
    bool negative = false;
    void add_edge(int u, int v, Cap cap, Cost cost)
    {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        E[u].push_back(m++);
        E[v].push_back(m++);
        if (cost < 0) negative = true;
    }
    pair<Cap, Cost> flow(int s, int t)
    {
        for (auto& edge : edges) edge.flow = 0;

        vector<Cost> pi(n, 0), dist(n, 0);
        vector<int> parent(n), vis(n);

        auto fix_potentials = [&]()
        {
            if (not vis[t]) return false;
            for (int u = 0; u < n; ++u)
                if (vis[u]) pi[u] += dist[u] - dist[t];
            return true;
        };
        auto spfa = [&]()
        {
            fill(all(dist), infcost), fill(all(vis), 0);
            queue<int> q; q.push(s); dist[s] = 0;
            while (not q.empty())
            {
                int v = q.front(); q.pop(); vis[v] = 1;
                for (auto idx : E[v])
                {
                    const auto& edge = edges[idx];
                    if (not edge.free()) continue;
                    if (chmin(dist[edge.to], dist[v] + edge.cost))
                        q.push(edge.to);
                }
            }
            return fix_potentials();
        };
        auto dijkstra = [&]()
        {
            fill(all(dist), infcost), fill(all(parent), -1), fill(all(vis), 0);
            struct Q
            {
                Cost key;
                int v;
                bool operator<(Q rhs) const { return key > rhs.key; }
            };
            priority_queue<Q> pq;
            pq.push({ 0, s }); dist[s] = 0;
            while (not pq.empty())
            {
                auto [d, v] = pq.top(); pq.pop();
                if (vis[v]++) continue;
                if (v == t) break;
                for (auto idx : E[v])
                {
                    const auto& edge = edges[idx];
                    if (vis[edge.to] || not edge.free()) continue;
                    Cost cost = edge.cost + pi[v] - pi[edge.to];
                    if (chmin(dist[edge.to], dist[v] + cost))
                    {
                        parent[edge.to] = idx;
                        pq.push({ dist[edge.to], edge.to });
                    }
                }
            }
            return fix_potentials();
        };

        if (negative) spfa();

        Cap flow = 0;
        Cost cost = 0;
        while (dijkstra())
        {
            Cap pushed = infcap;
            Cost price = 0;
            for (int v = t; v != s; v = edges[parent[v]].from)
                chmin(pushed, edges[parent[v]].free());
            for (int v = t; v != s; v = edges[parent[v]].from)
            {
                auto &edge = edges[parent[v]], &back = edges[parent[v] ^ 1];
                edge.flow += pushed, back.flow -= pushed;
                price += edge.cost;
            }
            flow += pushed, cost += price * pushed;
        }
        return { flow, cost };
    }
};

int main()
{ _
    exit(0);
}
