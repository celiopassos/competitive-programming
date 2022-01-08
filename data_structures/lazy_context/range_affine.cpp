template<typename T>
struct RangeAffine {
    // maps x -> a * x + b for each x in the range
    T a, b;
    RangeAffine(T a = 1, T b = 0) : a(a), b(b) {}
    template<typename Node>
    bool can_break(const Node& p) const {
        return false;
    }
    template<typename Node>
    bool can_apply(const Node& p) const {
        return true;
    }
    template<typename Node>
    void apply(Node& p) const {
        p.value = a * p.value + b * (p.r - p.l);
    }
    void compose(RangeAffine op) {
        b = op.a * b + op.b;
        a *= op.a;
    }
};
