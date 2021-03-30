template<typename T>
struct Clamp {
    static const T linf = numeric_limits<T>::min();
    static const T rinf = numeric_limits<T>::max();

    T low, high;
    Clamp(T low = linf, T high = rinf) : low(low), high(high) {}

    // composition, rhs is applied first, this is applied after
    Clamp operator+(Clamp rhs) const {
        if (high <= rhs.low) return Clamp(high, high);
        if (low >= rhs.high) return Clamp(low, low);
        return Clamp(max(low, rhs.low), min(high, rhs.high));
    }
    T operator()(T x) const { return std::clamp(x, low, high); }
};

template<typename T>
struct OffsetClamp {
    Clamp<T> cl;
    T add;

    OffsetClamp(Clamp<T> cl = Clamp<T>(), T add = 0) : cl(cl), add(add) {}
    OffsetClamp operator+(OffsetClamp rhs) const {
        Clamp<T> inside_cl(rhs.cl.low + add, rhs.cl.high + add);
        return OffsetClamp(cl + inside_cl, add + rhs.add);
    }
    T operator()(T x) { return cl(x + add); }
};
