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

template<typename T>
struct Dinic
{
    struct Edge
    {
        int from, to;
        T cap, flow = 0;
        T free() { return cap - flow; }
        Edge(int u, int v, T cap) : from(u), to(v), cap(cap) {}
    };
    vector<Edge> edges;
    const T inf = numeric_limits<T>::max();
    int n, m = 0;
    int logmax = 1, lim = 1;
    vector<vector<int>> E;
    vector<int> level, ptr;
    Dinic(int n) : n(n)
    {
        E.resize(n), level.resize(n), ptr.resize(n);
    }
    void add_edge(int u, int v, T cap)
    {
        if (cap == 0) return;
        edges.emplace_back(u, v, cap);
        edges.emplace_back(v, u, 0);
        E[u].push_back(m++);
        E[v].push_back(m++);
        logmax = max(logmax, __builtin_clzll(1LL) - __builtin_clzll(cap));
    }
    bool bfs(int s, int t)
    {
        fill(all(level), -1); level[s] = 0;
        static queue<int> q; q.push(s);
        while (not q.empty())
        {
            int u = q.front(); q.pop();
            for (auto idx : E[u])
            {
                int v = edges[idx].to;
                if (level[v] != -1 || edges[idx].free() < lim) continue;
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
        return level[t] != -1;
    }
    T push(int u, int t, T pushed)
    {
        if (u == t || pushed == 0) return pushed;
        for (int& idx = ptr[u]; idx < sz(E[u]); ++idx)
        {
            auto &edge = edges[E[u][idx]], &back = edges[E[u][idx] ^ 1];
            if (level[edge.to] != level[u] + 1 || edge.free() < lim) continue;
            T pushing = push(edge.to, t, min(pushed, edge.free()));
            if (pushing == 0) continue;
            edge.flow += pushing, back.flow -= pushing;
            return pushing;
        }
        return 0;
    }
    T flow(int s, int t, bool scale = false)
    {
        for (auto& edge : edges) edge.flow = 0;
        T f = 0;
        for (lim = scale ? (1 << logmax) : 1; lim > 0; lim >>= 1)
            while (bfs(s, t))
            {
                fill(all(ptr), 0);
                while (T pushed = push(s, t, inf)) f += pushed;
            }
        return f;
    }
};

int main()
{ _
    exit(0);
}
