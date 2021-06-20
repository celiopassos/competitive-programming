template<int K = 26, char offset = 'a'>
struct AhoCorasick {
    struct Node {
        int nxt[K], go[K];
        bool leaf = false, root = false;
        int p = -1, link = -1, leaflink = -1;
        char pc;
        Node(int p = -1, char pc = offset - 1) : p(p), pc(pc) {
            fill(begin(nxt), end(nxt), -1), fill(begin(go), end(go), -1);
        }
    };
    vector<Node> trie;
    AhoCorasick() {}
    int create() {
        int p = (int)size(trie);
        trie.emplace_back();
        trie[p].root = true;
        trie[p].link = trie[p].leaflink = p;
        return p;
    }
    int add(int rt, const string& s) {
        int u = rt;
        for (auto c : s) {
            int v = trie[u].nxt[c - offset];
            if (v == -1) {
                v = (int)size(trie);
                trie.emplace_back(u, c);
            }
            u = trie[u].nxt[c - offset] = v;
        }
        trie[u].leaflink = u, trie[u].leaf = true;
        return u;
    }
    void remove(int u) {
        trie[u].leaflink = -1, trie[u].leaf = false;
    }
    int getlink(int v) {
        if (trie[v].link == -1) {
            if (trie[trie[v].p].root) trie[v].link = trie[v].p;
            else trie[v].link = go(getlink(trie[v].p), trie[v].pc);
        }
        return trie[v].link;
    }
    int go(int v, char c) {
        int i = c - offset;
        if (trie[v].go[i] == -1) {
            if (trie[v].nxt[i] != -1) trie[v].go[i] = trie[v].nxt[i];
            else trie[v].go[i] = (trie[v].root ? v : go(getlink(v), c));
        }
        return trie[v].go[i];
    }
    // inclusive
    int getleaf(int v) {
        int &u = trie[v].leaflink;
        if (u == -1) u = getleaf(getlink(v));
        if (trie[u].leaflink != u) u = getleaf(u);
        return u;
    }
    // reports all occurrences in s (in order)
    // O(size(s) + number of occurrences) amortized
    template<typename F>
    void run(int rt, const string& s, F&& report) {
        int u = rt, n = (int)size(s);
        for (int i = 0; i < n; ++i) {
            u = go(u, s[i]);
            for (int v = getleaf(u); v != rt; v = getleaf(getlink(v))) report(i, v);
        }
    }
};
