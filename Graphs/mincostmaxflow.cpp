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
    const int n; int m = 0;
    const Cap inf = numeric_limits<Cap>::max();
    vector<Edge> edges;
    vector<vector<int>> E;
    vector<int> pi;

    MCMF(int n) : n(n) { E.resize(n), pi.resize(n); }
    void add_edge(int u, int v, Cap cap, Cost cost)
    {
        edges.emplace_back(u, v, cap, cost);
        edges.emplace_back(v, u, 0, -cost);
        E[u].push_back(m++), E[v].push_back(m++);
    }
    pair<Cap, Cost> flow(int s, int t)
    {
        auto spfa = [&]()
        {
            fill(all(pi), INF); pi[s] = 0;
            queue<int> q; q.push(s);
            while (not q.empty())
            {
                int u = q.front(); q.pop();
                for (auto idx : E[u])
                {
                    const auto& edge = edges[idx];
                    if (not edge.free()) continue;
                    if (chmin(pi[edge.to], pi[u] + edge.cost))
                        q.push(edge.to);
                }
            }
        };
        spfa(); // remove if no negative cost edges

        vector<Cap> dist(n);
        vector<int> parent(n);
        using ii = pair<Cap, int>;
        priority_queue<ii, vector<ii>, greater<ii>> pq;
        auto dijkstra = [&]()
        {
            fill(all(dist), inf), fill(all(parent), -1);
            pq.push(pair(0, s)); dist[s] = 0;
            while (not pq.empty())
            {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;
                for (auto idx : E[u])
                {
                    const auto& edge = edges[idx];
                    if (not edge.free()) continue;
                    int v = edge.to;
                    Cost cost = edge.cost + pi[u] - pi[v];
                    if (chmin(dist[v], dist[u] + cost))
                    {
                        parent[v] = idx;
                        pq.push(pair(dist[v], v));
                    }
                }
            }
            if (parent[t] == -1) return false;
            for (int u = 0; u < n; ++u)
                if (parent[u] != -1 || u == s) pi[u] += dist[u] - dist[t];
            return true;
        };

        Cap flow = 0;
        Cost cost = 0;
        while (dijkstra())
        {
            Cap pushed = inf;
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

