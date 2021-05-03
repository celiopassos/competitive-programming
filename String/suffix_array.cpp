template<typename ArrayType>
vector<int> sort_cyclic_shifts(const ArrayType& s) {
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

vector<int> suffix_array(const string& s) {
    auto p = sort_cyclic_shift(s + char(0));
    p.erase(begin(p));
    return p;
}

template<typename T>
vector<int> suffix_array(vector<T> s) {
    s.push_back(numeric_limits<T>::min());
    auto p = sort_cyclic_shift(s);
    p.erase(begin(p));
    return p;
}

template<typename S>
vector<int> lcp_array(const S& s, const vector<int>& p, const vector<int>& pos) {
    int n = (int)size(s);
    vector<int> lcp(n, 0);
    for (int i = 0, k = 0; i < n; ++i, k = max(0, k - 1)) {
        if (pos[i] == n - 1) {
            k = 0;
            continue;
        }
        for (int j = p[pos[i] + 1]; max(i, j) + k < n && s[i + k] == s[j + k]; ++k);
        lcp[pos[i]] = k;
    }
    return lcp;
}

template<typename RMQ>
int lcp_query(int i, int j, const vector<int>& pos, const RMQ& rmq) {
    if (i == j) return (int)size(pos) - i;
    if (pos[i] > pos[j]) swap(i, j);
    return rmq.query(pos[i] + 1, pos[j]);
}
