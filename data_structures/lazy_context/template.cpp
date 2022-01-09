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
