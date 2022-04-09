#ifndef ALGORITHMS_STRINGS_SUFFIX_TREE_HPP
#define ALGORITHMS_STRINGS_SUFFIX_TREE_HPP

#include "algorithms/common"

#include <stack>

struct SuffixTreeNode {
  int link, len, idx;
  SuffixTreeNode(int len, int idx) : link(-1), len(len), idx(idx) {}
};

std::vector<SuffixTreeNode> build_suffix_tree(
    const std::vector<int>& p, const std::vector<int>& lcp) {
  std::vector<SuffixTreeNode> st;
  std::stack<int> stk;
  auto create = [&](int len, int idx) {
    stk.push(st.size());
    st.emplace_back(len, idx);
  };
  create(0, -1);
  int N = p.size();
  for (int i = 1; i < N; ++i) {
    for (auto len : {N - 1 - p[i], lcp[i]}) {
      int l = p[i];
      while (st[stk.top()].len > len) {
        int v = stk.top();
        stk.pop();
        l = st[v].idx;
        if (len > st[stk.top()].len) {
          create(len, l);
        }
        st[v].link = stk.top();
      }
      if (len > st[stk.top()].len) {
        create(len, l);
      }
    }
  }
  int M = st.size();
  std::vector<int> V(M), label(M);
  std::iota(V.begin(), V.end(), 0);
  std::sort(V.begin(), V.end(), [&](int u, int v) { return st[u].len < st[v].len; });
  std::vector<SuffixTreeNode> relabeled;
  for (int j = 0; j < M; ++j) {
    label[V[j]] = j;
    relabeled.push_back(st[V[j]]);
  }
  for (int u = 1; u < M; ++u) {
    relabeled[u].link = label[relabeled[u].link];
  }
  return relabeled;
}

#endif  // ALGORITHMS_STRINGS_SUFFIX_TREE_HPP
