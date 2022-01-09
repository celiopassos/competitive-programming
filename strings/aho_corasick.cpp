struct AhoCorasick {
  struct Node {
    std::map<char, int> nxt, go;
    int p, link = -1, occ_link = -1;
    char c;
    Node(int p, char c) : p(p), c(c) {}
  };
  std::vector<Node> tr;
  AhoCorasick() {
    tr.emplace_back(0, 0);
    tr[0].occ_link = tr[0].link = 0;
  }
  int add_string(const std::string& s) {
    int u = 0;
    for (auto c : s) {
      if (!tr[u].nxt.count(c)) {
        int v = tr[u].go[c] = tr[u].nxt[c] = tr.size();
        tr.emplace_back(u, c);
        if (u == 0) tr[v].link = 0;
      }
      u = tr[u].nxt[c];
    }
    tr[u].occ_link = u;
    return u;
  }
  int get_link(int u) {
    if (tr[u].link == -1) {
      tr[u].link = go(get_link(tr[u].p), tr[u].c);
    }
    return tr[u].link;
  }
  int go(int u, char c) {
    if (!tr[u].go.count(c)) {
      tr[u].go[c] = (u == 0 ? 0 : go(get_link(u), c));
    }
    return tr[u].go[c];
  }
  int get_occurrence(int u) {
    if (tr[u].occ_link == -1) {
      tr[u].occ_link = get_occurrence(get_link(u));
    }
    return tr[u].occ_link;
  }
  template <typename Report>
  void run(const std::string& t, Report&& report) {
    for (int i = 0, u = 0; i < t.size(); ++i) {
      u = go(u, t[i]);
      for (int v = get_occurrence(u); v != 0; v = get_occurrence(get_link(v))) {
        report(i, v);
      }
    }
  }
};
