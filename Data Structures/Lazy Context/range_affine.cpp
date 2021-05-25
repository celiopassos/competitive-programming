// x -> a * x + b
template<typename T>
struct RangeAffine {
    using Type = T;
    inline static const Type Id = T(0);
    static Type op(Type x, Type y) { return x + y; }
    static bool cmp(Type x, Type y) { return x < y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    T a, b;
    RangeAffine(T a = 1, T b = 0) : a(a), b(b) {}
    void apply(Node& p) const {
        p.value = a * p.value + b * (p.r - p.l + 1);
    }
    void compose(RangeAffine op) {
        b = op.a * b + op.b;
        a *= op.a;
    }
};
