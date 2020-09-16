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

auto tarjan(const auto& E)
{
    int n = sz(E);
    vector low(n, -1), num(n, -1), scc(n, -1);

    vector active(n, 0);
    stack<int> st; int ct = 0;
    function<void(int)> dfs = [&](int u)
    {
        low[u] = num[u] = ct++;
        active[u] = 1; st.push(u);

        for (auto v : E[u])
        {
            if (num[v] == -1) dfs(v);
            if (active[v]) low[u] = min(low[u], low[v]);
        }

        if (low[u] == num[u]) do
        {
            scc[st.top()] = u;
            active[st.top()] = 0; st.pop();
        } while (not st.empty() && num[st.top()] >= num[u]);
    };

    for (int u = 0; u < n; ++u)
        if (num[u] == -1) dfs(u);

    return scc;
}

int main()
{ _
    exit(0);
}
