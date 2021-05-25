template<typename T>
struct RangeAssign {
    using Type = T;
    inline static const Type Id = T(0);
    static Type op(Type x, Type y) { return x + y; }
    static bool cmp(Type x, Type y) { return x < y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    inline static const T inf = numeric_limits<T>::max();
    T assign;
    RangeAssign(T assign = inf) : assign(assign) {}
    void apply(Node& p) const {
        if (assign != inf) p.value = assign * (p.r - p.l + 1);
    }
    void compose(RangeAssign op) {
        if (op.assign != inf) assign = op.assign;
    }
};
