// Build two range queries if the monoid is not commutative:
//  * stfor should combine like (x, y) -> x ∘ y,
//  * strev should combine like (x, y) -> y ∘ x.
//
// If the path is a = x1, x2, ..., xk = b, will return x1 ∘ x2 ∘ ... ∘ x_k.
//
// Unecessary if the monoid is commutative, or if the queries are
// always of the form v -> root or root -> v (take care of the order).

template<typename Monoid>
struct HLD
{
    using M = Monoid;
    using T = typename M::Type;

    const int n;
    const vector<vector<int>>& E;

    vector<int> parent, depth, heavy, head, pos;
    int cur_pos = 0;

    HLD(const auto& E, int root = 0) : n(size(E)), E(E),
        parent(n), depth(n), heavy(n, -1), head(n), pos(n)
    {
        parent[root] = root;
        dfs(root), decompose(root, root);
    }

    int dfs(int u)
    {
        int weight = 1, prv_max = 0;

        for (int v : E[u]) if (v != parent[u])
        {
            parent[v] = u, depth[v] = depth[u] + 1;
            int cur = dfs(v);
            weight += cur;
            if (cur > prv_max) prv_max = cur, heavy[u] = v;
        }

        return weight;
    }
    void decompose(int u, int h)
    {
        head[u] = h, pos[u] = cur_pos++;

        if (heavy[u] != -1) decompose(heavy[u], h);
        for (int v : E[u]) if (v != parent[u] && v != heavy[u])
            decompose(v, v);
    }
    // pass strev = stfor if Monoid is commutative
    T query(int a, int b, auto& stfor, auto& strev)
    {
        T left = M::Id, right = M::Id;

        while (head[a] != head[b])
        {
            if (depth[head[a]] > depth[head[b]])
            {
                left = M::op(left, strev.query(pos[head[a]], pos[a]));
                a = parent[head[a]];
            }
            else
            {
                right = M::op(stfor.query(pos[head[b]], pos[b]), right);
                b = parent[head[b]];
            }
        }

        if (depth[a] < depth[b])
            right = M::op(stfor.query(pos[a], pos[b]), right);
        else
            left = M::op(left, strev.query(pos[b], pos[a]));

        return M::op(left, right);
    }
    void update(int a, int b, auto& st, const auto& upd)
    {
        for (; head[a] != head[b]; a = parent[head[a]])
        {
            if (depth[head[b]] > depth[head[a]]) swap(a, b);
            st.update(pos[head[a]], pos[a], upd);
        }

        if (depth[a] > depth[b]) swap(a, b);
        st.update(pos[a], pos[b], upd);
    }
};
