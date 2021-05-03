template<int K, char offset>
struct ArrayState {
    using Type = char;
    int link, len, minlen, idx;
    bool clone = false;
    int nxt[K];
    ArrayState(int link = -1, int len = 0) : link(link), len(len) {
        fill(all(nxt), -1);
    }
    void set(char ch, int u) { nxt[ch - offset] = u; }
    int go(char ch) { return nxt[ch - offset]; }
};
 
template<typename T = char>
struct MapState {
    using Type = T;
    int link, len, minlen, idx;
    bool clone = false;
    map<T, int> nxt;
    MapState(int link = -1, int len = 0) : link(link), len(len) { }
    void set(T ch, int u) { nxt[ch] = u; }
    int go(T ch) { return nxt.count(ch) ? nxt[ch] : -1; }
};

template<typename State = ArrayState<26, 'a'>>
struct SuffixAutomaton {
    using T = typename State::Type;
    vector<State> st;
    SuffixAutomaton() : st(1) {}
    int last = 0, total_size = 0;
    void extend(T ch) {
        int u = last, len = st[last].len + 1;
        last = (int)size(st);
        for (; u != -1 && st[u].go(ch) == -1; u = st[u].link) st[u].set(ch, last);
        if (u == -1) st.emplace_back(0, len);
        else {
            int v = st[u].go(ch);
            if (st[u].len + 1 == st[v].len) st.emplace_back(v, len);
            else {
                int clone = last + 1;
                st.emplace_back(clone, len);
                st.push_back(st[v]);
                st[clone].len = st[u].len + 1, st[clone].clone = true;
                st[v].link = clone, st[v].minlen = st[clone].len + 1;
                for (int p = u; p != -1 && st[p].go(ch) == v; p = st[p].link) st[p].set(ch, clone);
            }
        }
        st[last].minlen = st[st[last].link].len + 1;
        st[last].idx = total_size++;
    }
    int go(int u, T ch) { return st[u].go(ch); }
    // sorts largest to smallest
    vector<int> topological_sort() const {
        int m = (int)size(st);
        vector<int> V(m), cnt(total_size + 1, 0);
        for (int u = 0; u < m; ++u) cnt[st[u].len] += 1;
        for (int x = total_size - 1; x >= 0; --x) cnt[x] += cnt[x + 1];
        for (int u = 0; u < m; ++u) V[--cnt[st[u].len]] = u;
        return V;
    }
};
