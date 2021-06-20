template<int K = 26, char offset = 'a'>
struct AhoCorasick {
    struct Node {
        int nxt[K], go[K];
        bool leaf = false;
        int p = -1, link = -1, leaflink = -1;
        char pc;
        Node(int p = -1, char pc = offset - 1) : p(p), pc(pc) {
            fill(begin(nxt), end(nxt), -1), fill(begin(go), end(go), -1);
        }
    };
    vector<Node> trie;
    AhoCorasick() : trie(1) {}
    int add(const string& s) {
        int u = 0;
        for (auto c : s) {
            int v = trie[u].nxt[c - offset];
            if (v == -1) {
                v = (int)size(trie);
                trie.emplace_back(u, c);
            }
            u = trie[u].nxt[c - offset] = v;
        }
        trie[u].leaf = true, trie[u].leaflink = u;
        return u;
    }
    void remove(int u) {
        trie[u].leaf = false, trie[u].leaflink = -1;
    }
    int getlink(int v) {
        if (trie[v].link == -1) {
            if (v == 0 || trie[v].p == 0) trie[v].link = 0;
            else trie[v].link = go(getlink(trie[v].p), trie[v].pc);
        }
        return trie[v].link;
    }
    int go(int v, char c) {
        int idx = c - offset;
        if (trie[v].go[idx] == -1) {
            if (trie[v].nxt[idx] != -1) trie[v].go[idx] = trie[v].nxt[idx];
            else trie[v].go[idx] = (v == 0 ? 0 : go(getlink(v), c));
        }
        return trie[v].go[idx];
    }
    // inclusive
    int getleaf(int v) {
        int &u = trie[v].leaflink;
        if (u == -1) {
            if (v == 0 || trie[v].leaf) u = v;
            else u = getleaf(getlink(v));
        }
        if (trie[u].leaflink != u) u = getleaf(u);
        return u;
    }
    // reports all occurrences in s (in order)
    // O(size(s) + number of occurrences) amortized
    template<typename F>
    void run(const string& s, F&& report) {
        int n = (int)size(s);
        for (int i = 0, u = 0; i < n; ++i) {
            u = go(u, s[i]);
            for (int v = getleaf(u); v != 0; v = getleaf(getlink(v))) report(i, v);
        }
    }
};
