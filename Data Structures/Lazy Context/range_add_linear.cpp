ll sum_idx(ll n) { return n * (n + 1) / 2; }
template<typename T>
struct RangeAddLinear {
    // adds a * (i - s) + b to the element in position i
    using Type = T;
    inline static const Type Id = T(0);
    static Type op(Type x, Type y) { return x + y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    T a, b;
    RangeAddLinear(T a = 0, T b = 0, int s = 0) : a(a), b(b - s * a) {}
    bool can_break(const Node& p) const { return false; }
    bool can_apply(const Node& p) const { return true; }
    void apply(Node& p) const {
        auto& v = p.value;
        v += a * (sum_idx(p.r) - sum_idx(p.l - 1)) + (p.r - p.l + 1) * b;
    }
    void compose(RangeAddLinear op) {
        a += op.a, b += op.b;
    }
};
