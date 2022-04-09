#ifndef ALGORITHMS_DATA_STRUCTURES_LAZY_CONTEXT_TEMPLATE_HPP
#define ALGORITHMS_DATA_STRUCTURES_LAZY_CONTEXT_TEMPLATE_HPP

template <typename T>
struct F {
  template <typename Node>
  bool can_break(const Node& p) const {
    return false;
  }
  template <typename Node>
  bool can_apply(const Node& p) const {
    return true;
  }
  template <typename Node>
  void apply(Node& p) const {}
  void compose(F op) {}
};

#endif  // ALGORITHMS_DATA_STRUCTURES_LAZY_CONTEXT_TEMPLATE_HPP
