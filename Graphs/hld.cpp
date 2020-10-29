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

template<typename T>
struct HLD
{
    vector<int> parent, depth, heavy, head, pos;
    const vector<vector<int>>& E;
    int cur_pos;
    HLD(const vector<vector<int>>& E) : E(E)
    {
        int n = size(E);
        parent.assign(n, 0);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        head.assign(n, 0);
        pos.assign(n, 0);
        cur_pos = 0;
        dfs(0, E);
        decompose(0, 0, E);
    }
    int dfs(int v)
    {
        int size = 1, max_c_size = 0;
        for (int c : E[v])
            if (c != parent[v])
            {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, E);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        return size;
    }
    void decompose(int v, int h)
    {
        head[v] = h, pos[v] = cur_pos++;

        if (heavy[v] != -1) decompose(heavy[v], h, E);

        for (int c : E[v])
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, E);
    }
    T query(int a, int b, auto& st)
    {
        T res = st.Tid;
        for (; head[a] != head[b]; b = parent[head[b]])
        {
            if (depth[head[a]] > depth[head[b]]) swap(a, b);
            T cur = st.query(pos[head[b]], pos[b]);
            res = st.combine(res, cur);
        }
        if (depth[a] > depth[b]) swap(a, b);
        T last = st.query(pos[a], pos[b]);
        res = st.combine(res, last);
        return res;
    }
};

int main()
{ _
    exit(0);
}

