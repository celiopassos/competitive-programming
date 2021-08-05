vector<int> sort_cyclic_shifts(const string& s) {
    int N = (int)s.size();
    vector<int> p(N), inv(N), tmp(N), cnt(N);
    iota(begin(p), end(p), 0);
    sort(begin(p), end(p), [&s](int i, int j){ return s[i] < s[j]; });
    inv[p[0]] = 0;
    for (int i = 1; i < N; ++i) {
        inv[p[i]] = inv[p[i - 1]] + (s[p[i]] != s[p[i - 1]] ? 1 : 0);
    }
    for (int shift = 1; shift < N; shift *= 2) {
        fill(begin(cnt), end(cnt), 0);
        for (int i = 0; i < N; ++i) {
            tmp[N - 1 - i] = (p[i] + N - shift) % N;
            cnt[inv[p[i]]] += 1;
        }
        partial_sum(begin(cnt), end(cnt), begin(cnt));
        for (auto i : tmp) p[--cnt[inv[i]]] = i;
        auto key = [&](int i) { return pair(inv[i], inv[(i + shift) % N]); };
        tmp[p[0]] = 0;
        for (int i = 1; i < N; ++i) {
            tmp[p[i]] = tmp[p[i - 1]] + (key(p[i - 1]) != key(p[i]) ? 1 : 0);
        }
        swap(tmp, inv);
    }
    return p;
}
struct SuffixArray {
    const string s;
    int N;
    vector<int> p, pos, lcp;
    SuffixArray(const string& s_) : s(s_ + char(0)), N((int)s.size()), pos(N, 0) {
        p = sort_cyclic_shifts(s);
        for (int i = 0; i < N; ++i) pos[p[i]] = i;
        build_lcp();
        build_suffix_tree();
    }
    void build_lcp() {
        lcp.assign(N, 0);
        for (int i = 0, k = 0; i < N - 1; ++i, k = max(0, k - 1)) {
            if (pos[i] == N - 1) {
                k = 0;
                continue;
            }
            for (int j = p[pos[i] + 1]; max(i, j) + k < N && s[i + k] == s[j + k]; ++k);
            lcp[pos[i]] = k;
        }
    }
    template<typename RMQ> int lcp_query(int i, int j, const RMQ& rmq) const {
        if (i == j) return (int)pos.size() - i;
        if (pos[i] > pos[j]) swap(i, j);
        return rmq.query(pos[i], pos[j] - 1);
    }
    // substring comparison
    template<typename RMQ> bool cmp(array<int, 2> S, array<int, 2> T, const RMQ& rmq) const {
        int lenS = S[1] - S[0] + 1, lenT = T[1] - T[0] + 1;
        int L = lcp_query(S[0], T[0], rmq);
        return L < min(lenS, lenT) ? s[S[0] + L] < s[T[0] + L] : lenS < lenT;
    }
    struct Node {
        int link, len, idx;
    };
    vector<Node> st;
    int create(int len, int idx) {
        st.push_back({-1 , len, idx});
        return (int)st.size() - 1;
    }
    void build_suffix_tree() {
        stack<int> stk;
        stk.push(create(0, -1));
        for (int i = 1; i < N; ++i) {
            for (auto len : {N - 1 - p[i], lcp[i]}) {
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
