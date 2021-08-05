template<typename T, typename F>
struct LazySegmentTree {
    struct Node {
        T value = T();
        F lazy = F();
        int l, r;
    };
    int N;
    vector<Node> st;
    int left(int p) const {
        return 2 * p + 1;
    }
    int right(int p) const {
        return 2 * p + 2;
    }
    void push(int p) {
        if (st[p].l + 1 == st[p].r) return;
        for (int q : {left(p), right(p)}) {
            st[p].lazy.apply(st[q]);
            st[q].lazy.compose(st[p].lazy);
        }
        st[p].lazy = F();
    }
    void update(int p, int ql, int qr, F f) {
        if (st[p].r <= ql || qr <= st[p].l || f.can_break(st[p])) {
            return;
        } else if (ql <= st[p].l && st[p].r <= qr && f.can_apply(st[p])) {
            f.apply(st[p]);
            st[p].lazy.compose(f);
        } else {
            push(p);
            update(left(p), ql, qr, f);
            update(right(p), ql, qr, f);
            st[p].value = st[left(p)].value + st[right(p)].value;
        }
    }
    T query(int p, int ql, int qr) {
        if (st[p].r <= ql || qr <= st[p].l) {
            return T();
        } else if (ql <= st[p].l && st[p].r <= qr) {
            return st[p].value;
        } else {
            push(p);
            return query(left(p), ql, qr) + query(right(p), ql, qr);
        }
    }
    template<typename Iterator>
    void build(int p, int l, int r, Iterator first) {
        st[p].l = l, st[p].r = r;
        if (l + 1 == r) {
            st[p].value = first[l];
        } else {
            int m = l + (r - l) / 2;
            build(left(p), l, m, first), build(right(p), m, r, first);
            st[p].value = st[left(p)].value + st[right(p)].value;
        }
    }
    void partition(vector<int>& q, int p, int ql, int qr) {
        if (st[p].r <= ql || qr <= st[p].l) {
            return;
        } else if (ql <= st[p].l && st[p].r <= qr) {
            q.push_back(p);
        } else {
            push(p);
            partition(q, left(p), ql, qr);
            partition(q, right(p), ql, qr);
        }
    }
    template<typename Pred>
    int binary_search(int p, T prefix, Pred&& pred) {
        if (st[p].l + 1 == st[p].r) {
            return st[p].l;
        } else {
            push(p);
            T nprefix = prefix + st[left(p)].value;
            if (pred(nprefix)) {
                return binary_search(right(p), nprefix, pred);
            } else {
                return binary_search(left(p), prefix, pred);
            }
        }
    }
    template<typename Iterator>
    LazySegmentTree(Iterator first, Iterator last) : N(int(last - first)), st(4 * N) {
        build(0, 0, N, first);
    }
    T query(int l, int r) {
        return query(0, l, r);
    }
    void update(int l, int r, F f) {
        update(0, l, r, f);
    }
    int lower_bound(int l, int r, T target) {
        return find_right(l, r, [target](T value) { return value < target; });
    }
    // returns first i in [l, r) with pred(query(l, i + 1)) == false (r if no such i exists)
    template<typename Pred>
    int find_right(int l, int r, Pred&& pred) {
        static vector<int> q;
        partition(q, 0, l, r);
        int res = r;
        T prefix = T();
        for (auto p : q) {
            T nprefix = prefix + st[p].value;
            if (pred(nprefix)) {
                prefix = nprefix;
            } else {
                res = binary_search(p, prefix, pred);
                break;
            }
        }
        q.clear();
        return res;
    }
};
