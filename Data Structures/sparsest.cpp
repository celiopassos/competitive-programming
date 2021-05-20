template<typename T>
struct F1 {
    using Type = T;
    inline const static T Tid = T(0);
    inline const static F1 Fid = F1(0);
    T add;
    explicit F1(T add) : add(add) {}
    void apply(T& old, int L, int R) const {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op, int L, int R) {
        add += op.add; (void)L, (void)R;
    }
    bool operator==(const F1& op) const { return add == op.add; }
    static T op(const T& lhs, const T& rhs) {
        return lhs + rhs;
    }
};

template<typename F>
struct SparseST {
    using T = typename F::Type;

    int L, R;

    vector<T> st;
    vector<F> lazy;
    vector<int> LEFT, RIGHT;

    int create() {
        st.push_back(F::Tid), lazy.push_back(F::Fid), LEFT.push_back(-1), RIGHT.push_back(-1);
        return (int)size(st) - 1;
    }

    int left(int p) { return LEFT[p] == -1 ? (LEFT[p] = create()) : LEFT[p]; }
    int right(int p) { return RIGHT[p] == -1 ? (RIGHT[p] = create()) : RIGHT[p]; }

    void push(int p, int l, int r) {
        if (lazy[p] == F::Fid) return; // may wanna remove this...

        lazy[p].apply(st[p], l, r);

        if (l != r) {
            int m = l + (r - l) / 2;

            lazy[left(p)].compose(lazy[p], l, m);
            lazy[right(p)].compose(lazy[p], m + 1, r);
        }

        lazy[p] = F::Fid;
    }
    void update(int p, int l, int r, int ql, int qr, F op) {
        if (r < ql || qr < l) push(p, l, r);
        else if (ql <= l && r <= qr) {
            lazy[p].compose(op, l, r);
            push(p, l, r);
        }
        else {
            int m = l + (r - l) / 2;

            push(p, l, r);

            update(left(p), l, m, ql, qr, op);
            update(right(p), m + 1, r, ql, qr, op);

            st[p] = F::combine(st[left(p)], st[right(p)]);
        }
    }
    T query(int p, int l, int r, int ql, int qr) {
        if (p == -1 || r < ql || qr < l) return F::Tid;

        push(p, l, r);

        if (ql <= l && r <= qr) return st[p];

        int m = l + (r - l) / 2;

        T resl = query(LEFT[p], l, m, ql, qr);
        T resr = query(RIGHT[p], m + 1, r, ql, qr);

        return F::combine(resl, resr);
    }
    SparseST(int L, int R) : L(L), R(R) { create(); }
    void update(int l, int r, F op) {
        update(0, L, R, l, r, op);
    }
    T query(int l, int r) {
        return query(0, L, R, l, r);
    }
};
