#ifndef ALGORITHMS_DATA_STRUCTURES_LI_CHAO_TREE_HPP
#define ALGORITHMS_DATA_STRUCTURES_LI_CHAO_TREE_HPP

#include <deque>

// pass Cmp = std::less<Y> for min queries or greater<Y> for std::max queries
template <typename F, typename X, typename Y, typename Cmp>
struct LiChaoTree {
  struct Node {
    F f = F();
    X l, r, m;
    Node(X l, X r) : l(l), r(r), m(l + (r - l) / 2) {}
    Node *left = nullptr, *right = nullptr;
  };

  Cmp cmp;
  LiChaoTree(Cmp cmp = Cmp()) : cmp(cmp) {}

  std::deque<Node> deq;
  Node *create(X l, X r) {
    return &deq.emplace_back(l, r);
  }

  Node *left(Node *p) {
    return p->left ? p->left : p->left = create(p->l, p->m);
  }
  Node *right(Node *p) {
    return p->right ? p->right : p->right = create(p->m, p->r);
  }

  void add(Node *p, F g) {
    if (cmp(g(p->m), (p->f)(p->m))) {
      std::swap(p->f, g);
    }
    if (p->r - p->l > 1) {
      if (cmp(g(p->l), (p->f)(p->l))) {
        add(left(p), g);
      } else if (cmp(g(p->r - 1), (p->f)(p->r - 1))) {
        add(right(p), g);
      }
    }
  }

  Y query(Node *p, X x) {
    Y res = (p->f)(x);
    if (x < p->m && p->left) {
      Y y = query(p->left, x);
      if (cmp(y, res)) res = y;
    } else if (x > p->m && p->right) {
      Y y = query(p->right, x);
      if (cmp(y, res)) res = y;
    }
    return res;
  }
};

#endif  // ALGORITHMS_DATA_STRUCTURES_LI_CHAO_TREE_HPP
