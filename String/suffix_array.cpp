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
    void build_lcp() {
        lcp.assign(n, 0);
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
        st.push_back({-1 , len, idx});
        return (int)size(st) - 1;
    }
    void build_suffix_tree() {
        stack<int> stk;
        stk.push(create(0, -1));
        for (int i = 1; i < n; ++i) {
            for (auto len : { n - 1 - p[i], lcp[i] }) {
                int l = p[i];
                while (st[stk.top()].len > len) {
                    int v = stk.top();
                    stk.pop();
                    l = st[v].idx;
                    if (len > st[stk.top()].len) stk.push(create(len, l));
                    st[v].link = stk.top();
                }
                if (len > st[stk.top()].len) stk.push(create(len, l));
            }
        }
    }
};
