// needs to build with an array of pairs where the second element is the index
// adds a * (i - s) + b to the element in position i

template<typename T>
struct RangeAddLinear {
    using Type = pair<T, ll>;
    inline static const Type Id = Type(0, 0);
    static Type op(Type x, Type y) {
        return {x.first + y.first, x.second + y.second};
    }
    static bool cmp(Type x, Type y) { return x < y; }
    struct Node {
        Type value = Id;
        int l, r;
    };
    T a, b;
    RangeAddLinear(T a = 0, T b = 0, int s = 0) : a(a), b(b - s * a) {}
    void apply(Node& p) const {
        auto& v = p.value;
        v.first += a * v.second + (p.r - p.l + 1) * b;
    }
    void compose(RangeAddLinear op) {
        a += op.a, b += op.b;
    }
};
