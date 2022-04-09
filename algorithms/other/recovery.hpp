#ifndef ALGORITHMS_OTHER_RECOVERY_HPP
#define ALGORITHMS_OTHER_RECOVERY_HPP

template <typename T>
struct Recovery {
  struct Node {
    T value;
    Node* prev;
    Node(T value, Node* prev) : value(value), prev(prev) {}
  };
  std::deque<Node> states;
  Node* create(T value, Node* prev) {
    return &states.emplace_back(value, prev);
  }
  std::vector<T> recover(Node* last) {
    std::vector<T> res;
    while (last != nullptr) {
      res.push_back(last->value);
      last = last->prev;
    }
    std::reverse(res.begin(), res.end());
    return res;
  }
};

#endif  // ALGORITHMS_OTHER_RECOVERY_HPP
