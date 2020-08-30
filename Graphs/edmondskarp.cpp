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

// xz

int n;
vvi C;
vvi E;

int bfs(int s, int t, vi& p)
{
    fill(p.begin(), p.end(), -1);
    p[s] = -2;

    queue<ii> q;
    q.push({s, INF});

    while (not q.empty())
    {
        int u = q.front().f;
        int flow = q.front().s;
        q.pop();

        for (int v : E[u])
            if (p[v] == -1 && C[u][v])
            {
                p[v] = u;
                int new_flow = min(flow, C[u][v]);
                if (v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
    }

    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0;
    vi p(n);
    int new_flow;
    while ((new_flow = bfs(s, t, p)))
    {
        flow += new_flow;

        int v = t;
        while (v != s)
        {
            int u = p[v];
            C[u][v] -= new_flow;
            C[v][u] += new_flow;
            v = u;
        }
    }

    return flow;
}

int main()
{ _
    exit(0);
}

