template<int K = 26, char offset = 'a'>
struct SuffixAutomaton {
    struct State {
        int link, len, minlen, idx;
        int nxt[K];
        bool clone = false;
        State(int link = -1, int len = 0) : link(link), len(len) { fill(all(nxt), -1); }
    };
    vector<State> st;

    SuffixAutomaton(const string& s) : st(1) {
        for (auto c : s) extend(c);
    }

    int last = 0, total_size = 0;
    void extend(char c) {
        int u = last, len = st[last].len + 1, ch = c - offset;
        last = (int)size(st);

        for (; u != -1 && st[u].nxt[ch] == -1; u = st[u].link) st[u].nxt[ch] = last;

        if (u == -1) {
            st.emplace_back(0, len);
        }
        else if (int v = st[u].nxt[ch]; st[u].len + 1 == st[v].len) {
            st.emplace_back(v, len);
        }
        else {
            int clone = last + 1;
            st.emplace_back(clone, len);
            st.push_back(st[v]);

            st[clone].len = st[u].len + 1, st[clone].clone = true;
            st[v].link = clone, st[v].minlen = st[clone].len + 1;

            for (int p = u; p != -1 && st[p].nxt[ch] == v; p = st[p].link) st[p].nxt[ch] = clone;
        }

        st[last].minlen = st[st[last].link].len + 1;
        st[last].idx = total_size++;
    }
    int go(int u, char c) const { return st[u].nxt[c - offset]; }
};
