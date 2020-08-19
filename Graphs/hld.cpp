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

template<typename T>
struct HLD
{
    vi parent, depth, heavy, head, pos;
    const vector<vi>& E;
    int cur_pos;

    HLD(const vector<vi>& E) : E(E)
    {
        int n = sz(E);

        parent = vi(n);
        depth = vi(n);
        heavy = vi(n, -1);
        head = vi(n);
        pos = vi(n);
        cur_pos = 0;

        dfs(0, E);
        decompose(0, 0, E);
    }

    int dfs(int v)
    {
        int size = 1;
        int max_c_size = 0;
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

        if (heavy[v] != -1)
            decompose(heavy[v], h, E);

        for (int c : E[v])
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, E);
    }

    T query(int a, int b, SegmentTree<T> st)
    {
        T res = st.default_value;
        for (; head[a] != head[b]; b = parent[head[b]])
        {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);

            T cur = st.query(pos[head[b]], pos[b]);
            res = st.combine(res, cur);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        T last = st.query(pos[a], pos[b]);
        res = st.combine(res, last);
        return res;
    }
};

int main()
{ _
    exit(0);
}

