template<typename T>
struct F {
    using Type = T;
    inline static const Type Id = T();
    static Type op(Type x, Type y) {
        return Id;
    }
    struct Node {
        Type value = Id;
        int l, r;
    };
    bool can_break(const Node& p) const { return false; }
    bool can_apply(const Node& p) const { return true; }
    void apply(Node& p) const {
    }
    void compose(F op) {
    }
};
