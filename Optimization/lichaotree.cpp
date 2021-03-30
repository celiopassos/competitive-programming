// May define any kind of function,
// as long as intersections are unique.
// Should default to constant = infinity

// E.g., linear function:

template<typename T>
struct Linear {
    T a = 0, b = numeric_limits<T>::max();
    T operator()(T x) const { return a * x + b; }
};

template<typename Func, typename Domain>
struct LiChaoTree {
    Domain L, R;
    Func inf = Func();
    vector<Func> st;
    vector<int> LEFT, RIGHT;

    LiChaoTree(Domain L, Domain R) : L(L), R(R) { create(); }

    int create() {
        LEFT.push_back(-1), RIGHT.push_back(-1);
        st.push_back(inf);
        return size(st) - 1;
    }
    int left(int p) { return LEFT[p] == -1 ? LEFT[p] = create() : LEFT[p]; }
    int right(int p) { return RIGHT[p] == -1 ? RIGHT[p] = create() : RIGHT[p]; }

    bool is_inf(const Func& f) const {
        return f(L) == inf(L) && f(R - 1) == inf(R - 1);
    }
    void update(Func add) {
        Domain l = L, r = R; int p = 0;
        while (l < r) {
            Domain m = l + (r - l) / 2;
            bool lft = add(l) < st[p](l);
            bool mid = add(m) < st[p](m);
            if (mid) swap(add, st[p]);
            if (r - l == 1 || is_inf(add)) break;
            if (lft != mid) p = left(p), r = m;
            else p = right(p), l = m + 1;
        }
    }
    auto query(Domain x) // returns minimum {
        auto res = inf(x);
        Domain l = L, r = R;
        int p = 0;
        while (l < r) {
            res = min(res, st[p](x));
            Domain m = l + (r - l) / 2;
            if (m == x || is_inf(st[p])) break;
            else if (x < m) p = left(p), r = m;
            else p = right(p), l = m + 1;
        }
        return res;
    }
    int (size)() const { return size(st); }
};
