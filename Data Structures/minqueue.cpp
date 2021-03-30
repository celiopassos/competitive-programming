template<typename T>
struct M1 {
    using Type = T;
    inline const static T Id = INF;
    static T op(const T& x, const T& y) { return min(x, y); }
};

template<typename Monoid, bool top_down = false>
class MinimumStack {
private:
    using M = Monoid;
    using T = typename M::Type;
    stack<pair<T, T>> st;
public:
    T top() const { return st.top().first; }
    T minimum() const { return st.empty() ? M::Id : st.top().second; }
    void push(T value) {
        if (top_down)
            st.push(pair<T, T>(value, M::op(value, minimum())));
        else
            st.push(pair<T, T>(value, M::op(minimum(), value)));
    }
    void pop() { st.pop(); }
    bool empty() const { return st.empty(); }
    int (size)() const { return size(st); }
};

template<typename Monoid>
class MinimumQueue {
private:
    using M = Monoid;
    using T = typename Monoid::Type;
    MinimumStack<Monoid, false> in;
    MinimumStack<Monoid, true> out;
    void move() {
        if (out.empty()) while (not in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }
public:
    T front() { move(); return out.top(); }
    T minimum() const { return M::op(out.minimum(), in.minimum()); }
    void push(T value) { in.push(value); }
    void pop() { move(); out.pop(); }
    bool empty() const { return in.empty() && out.empty(); }
    int (size)() const { return size(in) + size(out); }
};
