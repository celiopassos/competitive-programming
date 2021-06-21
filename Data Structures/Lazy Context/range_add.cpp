template<typename T>
struct RangeAdd {
    using Type = T;
    inline static const Type Id = T(0);
    static Type op(Type x, Type y) { return x + y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    T add;
    RangeAdd(T add = 0) : add(add) {}
    void apply(Node& p) const {
        p.value = p.value + add * (p.r - p.l + 1);
    }
    void compose(RangeAdd op) {
        add += op.add;
    }
};
