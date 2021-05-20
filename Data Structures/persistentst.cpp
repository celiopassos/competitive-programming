template<typename T>
struct M1 {
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
};

template<typename Monoid>
struct PersistentST {
    using M = Monoid;
    using T = typename Monoid::Type;
    struct Node {
        T value = M::Id;
        int left = -1, right = -1, root;
        Node (int root) : root(root) {}
    };
    int n;
    deque<Node> st;
    int num_nodes;

    int create(int rt = -1) {
        if (rt == -1) rt = num_nodes;
        st.emplace_back(rt);
        return num_nodes++;
    }
    inline T get(int p) { return p == -1 ? M::Id : st[p].value; }

    // p must be a reference!
    void modify(int rt, int &p, int l, int r, int pos, T value) {
        if (p == -1) p = create(rt);
        else if (st[p].root != rt) {
            int temp = p;
            p = create();
            st[p] = st[temp], st[p].root = rt;
        }
        if (l == r) st[p].value = value;
        else {
            int m = l + (r - l) / 2;
            pos <= m ? modify(rt, st[p].left, l, m, pos, value) : modify(rt, st[p].right, m + 1, r, pos, value);
            st[p].value = M::op(get(st[p].left), get(st[p].right));
        }
    }
    T query(int p, int l, int r, int ql, int qr) {
        if (p == -1 || r < ql || qr < l) return M::Id;
        if (ql <= l && r <= qr) return st[p].value;
        int m = l + (r - l) / 2;
        T resl = query(st[p].left, l, m, ql, qr);
        T resr = query(st[p].right, m + 1, r, ql, qr);
        return M::op(resl, resr);
    }
    int merge(int rt, int p, int q) {
        if (p == -1) return q;
        if (q == -1) return p;
        int r = create(rt);
        st[r].value = M::op(get(p), get(q));
        st[r].left = merge(rt, st[p].left, st[q].left);
        st[r].right = merge(rt, st[p].right, st[q].right);
        return r;
    }
    void build(int rt, int p, int l, int r, const vector<T>& a) {
        if (l == r) st[p].value = a[l];
        else {
            int m = l + (r - l) / 2;
            st[p].left = create(rt), st[p].right = create(rt);
            build(rt, st[p].left, l, m, a), build(rt, st[p].right, m + 1, r, a);
            st[p].value = M::op(get(st[p].left), get(st[p].right));
        }
    }
    PersistentST(int n) : n(n), num_nodes(0) { create(); }
    int build(const vector<T>& a) {
        assert(size(a) == n);
        int rt = create();
        build(rt, rt, 0, n - 1, a);
        return rt;
    }
    int duplicate(int root) {
        int rt = create();
        st[rt] = st[root];
        st[rt].root = rt;
        return rt;
    }
    // doesn't make sense with uncommutative operations, versions are not modified
    // O(size of tree overlap)
    int merge(int root1, int root2) {
        return merge(num_nodes, root1, root2);
    }
    // modifies version in place
    void modify(int root, int pos, T value) {
        modify(root, root, 0, n - 1, pos, value);
    }
    T query(int root, int l, int r) {
        return query(root, 0, n - 1, l, r);
    }
};
