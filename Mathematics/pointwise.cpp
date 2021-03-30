template<typename...>
struct Pointwise {
    Pointwise() { }
    Pointwise(auto init) { (void)init; }
    auto get() { return tuple<>(); }
};

template<typename T, typename... Ts>
struct Pointwise<T, Ts...> {
    static constexpr bool base = (sizeof...(Ts) == 0);
    T value;
    Pointwise<Ts...> nxt;
    Pointwise(T value, Ts... args) : value(value), nxt(args...) { }
    Pointwise(auto init) : value(init), nxt(init) { }
    Pointwise() : value(T()), nxt() { }
    template<typename Op>
    void apply(const Pointwise& rhs, Op&& op) {
        value = op(value, rhs);
        if constexpr (not base) nxt.apply(rhs.nxt, op);
    }
    Pointwise& operator+=(const Pointwise& rhs) { apply(rhs, plus<T>()); return *this; };
    Pointwise& operator-=(const Pointwise& rhs) { apply(rhs, minus<T>()); return *this; };
    Pointwise& operator*=(const Pointwise& rhs) { apply(rhs, multiplies<T>()); return *this; };
    Pointwise& operator/=(const Pointwise& rhs) { apply(rhs, divides<T>()); return *this; };
    Pointwise& operator%=(const Pointwise& rhs) { apply(rhs, modulus<T>()); return *this; };
    Pointwise operator+(const Pointwise& rhs) const { return Pointwise(*this) += rhs; };
    Pointwise operator-(const Pointwise& rhs) const { return Pointwise(*this) -= rhs; };
    Pointwise operator*(const Pointwise& rhs) const { return Pointwise(*this) *= rhs; };
    Pointwise operator/(const Pointwise& rhs) const { return Pointwise(*this) /= rhs; };
    bool operator<(const Pointwise& rhs) const {
        if constexpr (base) return value < rhs.value;
        else if (value == rhs.value) return nxt < rhs.nxt;
        else return value < rhs.value;
    }
    bool operator==(const Pointwise& rhs) const {
        if constexpr (base) return value == rhs.value;
        else return value == rhs.value && nxt == rhs.nxt;
    }
    auto get() { return tuple_cat(tuple<T&>(value), nxt.get()); }
};
