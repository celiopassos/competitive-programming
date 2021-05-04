#include "bits/stdc++.h"

using namespace std;

#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(x) begin(x), end(x)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

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
            int u = -1;
            if (int sufflen = n - 1 - p[i]; lcp[i] < sufflen) {
                u = create(sufflen, p[i]);
                if (lcp[i - 1] >= lcp[i]) st[u].link = stk.top(), u = -1;
            }
            while (st[stk.top()].len > lcp[i]) {
                int v = stk.top();
                stk.pop();
                if (lcp[i] > st[stk.top()].len) stk.push(create(lcp[i], p[i]));
                st[v].link = stk.top();
            }
            if (lcp[i] > st[stk.top()].len) stk.push(create(lcp[i], p[i]));
            if (u != -1) st[u].link = stk.top();
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    string s;
    cin >> s;
 
    SuffixArray sa(s);
    sa.build_lcp();
    sa.build_suffix_tree();
 
    const auto& st = sa.st;
    int m = (int)size(st);
 
    vector<int> V(m - 1);
    iota(all(V), 1);
    sort(all(V), [&](int u, int v){ return st[u].len > st[v].len; });
 
    vector<set<int>> S(m);
    for (int u = 1; u < m; ++u) S[u].insert(st[u].idx);
 
    int k = 1;
    for (auto u : V) {
        int p = st[u].link;
        assert(p != -1);

        if (size(S[p]) < size(S[u])) swap(S[p], S[u]);
        for (auto i : S[u]) {
            auto [iter, check] = S[p].insert(i);
            if (not check) continue;
 
            if (iter != begin(S[p])) k = max(k, 1 + st[p].len / (i - *prev(iter)));
            if (next(iter) != end(S[p])) k = max(k, 1 + st[p].len / (*next(iter) - i));
        }
    }
 
    cout << k << endl;
 
    exit(0);
}
