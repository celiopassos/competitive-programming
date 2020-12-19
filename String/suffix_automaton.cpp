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

template<int K = 26, char offset = 'a'>
struct SuffixAutomaton
{
    struct State
    {
        int link, len;
        int nxt[K];
        bool terminal = false;
        State(int link = -1, int len = 0) : link(link), len(len) { fill(all(nxt), -1); }
    };
    vector<State> state = { State() };

    int last = 0;
    void extend(char c)
    {
        int cur = size(state), u = last, len = state[last].len + 1, ch = c - offset;

        for (;u != -1 && state[u].nxt[ch] == -1; u = state[u].link)
            state[u].nxt[ch] = cur;

        last = cur;

        if (u == -1)
        {
            state.emplace_back(0, len);
        }
        else if (int v = state[u].nxt[ch]; state[u].len + 1 == state[v].len)
        {
            state.emplace_back(v, len);
        }
        else
        {
            int clone = cur + 1;
            state.emplace_back(clone, len);
            state.push_back(state[v]);
            state[clone].len = state[u].len + 1;
            state[v].link = clone;
            for (int p = u; p != -1 && state[p].nxt[ch] == v; p = state[p].link)
                state[p].nxt[ch] = clone;
        }
    }

    SuffixAutomaton(const string& s)
    {
        for (auto c : s) extend(c);
        for (int v = last; v != -1; v = state[v].link)
            state[v].terminal = true;
    }

    int go(int u, char c) const
    {
        return state[u].nxt[c - offset];
    }

    vector<int> topological_sort() const
    {
        int m = size(state);

        vector<int> indeg(m, 0);

        for (int u = 0; u < m; ++u)
            for (char c = offset; c < offset + K; ++c)
                if (int v = go(u, c); v != -1) indeg[v] += 1;

        static queue<int> q;

        for (int u = 0; u < m; ++u) if (indeg[u] == 0) q.push(u);

        vector<int> topo;

        while (not empty(q))
        {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (char c = offset; c < offset + K; ++c)
                if (int v = go(u, c); v != -1 && --indeg[v] == 0) q.push(v);
        }

        return topo;
    }
};

int main()
{ _
    exit(0);
}
