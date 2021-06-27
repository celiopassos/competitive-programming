template<typename T>
struct RangeAffine {
    // x -> a * x + b
    using Type = T;
    inline static const Type Id = T(0);
    static Type op(Type x, Type y) { return x + y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    T a, b;
    RangeAffine(T a = 1, T b = 0) : a(a), b(b) {}
    bool can_break(const Node& p) const { return false; }
    bool can_apply(const Node& p) const { return true; }
    void apply(Node& p) const {
        p.value = a * p.value + b * (p.r - p.l + 1);
    }
    void compose(RangeAffine op) {
        b = op.a * b + op.b;
        a *= op.a;
    }
};
