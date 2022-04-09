#ifndef ALGORITHMS_DATA_STRUCTURES_MONOID_QUEUE_HPP
#define ALGORITHMS_DATA_STRUCTURES_MONOID_QUEUE_HPP

#include "algorithms/common"

#include <stack>

template <typename T, bool top_down>
struct MonoidStack {
  std::stack<std::pair<T, T>> st;
  T top() const {
    return st.top().first;
  }
  T result() const {
    return st.empty() ? T() : st.top().second;
  }
  void push(T value) {
    st.emplace(value, top_down ? value + result() : result() + value);
  }
  void pop() {
    st.pop();
  }
  bool empty() const {
    return st.empty();
  }
  size_t size() const {
    return st.size();
  }
};

template <typename T>
struct MonoidQueue {
  MonoidStack<T, false> in;
  MonoidStack<T, true> out;
  void move() {
    if (out.empty()) {
      while (!in.empty()) {
        out.push(in.top());
        in.pop();
      }
    }
  }
  T front() {
    move();
    return out.top();
  }
  T result() const {
    return out.result() + in.result();
  }
  void push(T value) {
    in.push(value);
  }
  void pop() {
    move();
    out.pop();
  }
  bool empty() const {
    return in.empty() && out.empty();
  }
  size_t size() const {
    return in.size() + out.size();
  }
};

#endif  // ALGORITHMS_DATA_STRUCTURES_MONOID_QUEUE_HPP
