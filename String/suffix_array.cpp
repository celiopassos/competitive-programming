vector<int> sort_cyclic_shifts(const string& s) {
    int n = (int)size(s);
    vector<int> p(n), inv(n), tmp(n), cnt(n);
    iota(all(p), 0);
    sort(all(p), [&s](int i, int j){ return s[i] < s[j]; });
    inv[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
        inv[p[i]] = inv[p[i - 1]] + (s[p[i]] != s[p[i - 1]] ? 1 : 0);
    }
    for (int shift = 1; shift < n; shift *= 2) {
        fill(all(cnt), 0);
        for (int i = 0; i < n; ++i) {
            tmp[n - 1 - i] = (p[i] + n - shift) % n;
            cnt[inv[p[i]]] += 1;
        }
        partial_sum(all(cnt), begin(cnt));
        for (auto i : tmp) p[--cnt[inv[i]]] = i;
        auto key = [&](int i) { return pair(inv[i], inv[(i + shift) % n]); };
        tmp[p[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tmp[p[i]] = tmp[p[i - 1]] + (key(p[i - 1]) != key(p[i]) ? 1 : 0);
        }
        swap(tmp, inv);
    }
    return p;
}

struct SuffixArray {
    const string s;
    const int n;
    vector<int> p, pos, lcp;
    SuffixArray(const string& s_) : s(s_ + char(0)), n((int)size(s)), pos(n, 0) {
        p = sort_cyclic_shifts(s);
        for (int i = 0; i < n; ++i) pos[p[i]] = i;
    }
    // lcp[0] = 0, lcp[i] = longest common prefix of p[i - 1] and p[i] for i > 0
    void build_lcp() {
        lcp.assign(n - 1, 0);
        for (int i = 0, k = 0; i < n - 1; ++i, k = max(0, k - 1)) {
            if (pos[i] == n - 1) {
                k = 0;
                continue;
            }
            for (int j = p[pos[i] + 1]; max(i, j) + k < n && s[i + k] == s[j + k]; ++k);
            lcp[pos[i]] = k;
        }
    }
    template<typename RMQ> int lcp_query(int i, int j, const RMQ& rmq) const {
        if (i == j) return (int)size(pos) - i;
        if (pos[i] > pos[j]) swap(i, j);
        return rmq.query(pos[i], pos[j] - 1);
    }
    struct Node {
        int link, len, idx;
    };
    vector<Node> st;
    int create(int len, int idx) {
        st.push_back({-1 , len, 0, idx});
        return (int)size(st) - 1;
    }
    void set_link(int u, int p) {
        st[u].link = p, st[u].minlen = st[p].len + 1;
    }
    void build_suffix_tree() {
        stack<int> stk, children;
        stk.push(create(0, -1));
        for (int i = 1; i < n - 1; ++i) {
            int sufflen = n - 1 - p[i];
            if (lcp[i] < sufflen) {
                int u = create(sufflen, p[i]);
                if (lcp[i] <= lcp[i - 1]) set_link(u, stk.top());
                else children.push(u);
            }
            while (st[stk.top()].len > lcp[i]) {
                int v = stk.top();
                stk.pop();
                if (st[stk.top()].len >= lcp[i]) set_link(v, stk.top());
                else children.push(v);
            }
            if (lcp[i] > st[stk.top()].len) {
                stk.push(create(lcp[i], p[i]));
                while (not empty(children)) {
                    set_link(children.top(), stk.top());
                    children.pop();
                }
            }
        }
        stk.push(create(n - 1 - p.back(), p.back()));
        while (size(stk) > 1) {
            int u = stk.top();
            stk.pop();
            set_link(u, stk.top());
        }
    }
};
