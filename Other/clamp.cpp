template<typename T>
struct Clamp {
    static const T linf = numeric_limits<T>::min() / 2, rinf = numeric_limits<T>::max() / 2;
    T low, high;
    Clamp(T low = linf, T high = rinf) : low(low), high(high) {}
    // composition, rhs is applied first, *this is applied after
    Clamp operator*(Clamp rhs) const {
        if (high <= rhs.low) return Clamp(high, high);
        if (low >= rhs.high) return Clamp(low, low);
        return Clamp(max(low, rhs.low), min(high, rhs.high));
    }
    T operator()(T x) const {
        return std::clamp(x, low, high);
    }
};
template<typename T>
struct OffsetClamp : Clamp<T> {
    using Clamp<T>::linf;
    using Clamp<T>::rinf;
    T add;
    OffsetClamp(T low = linf, T high = rinf, T add = 0) : Clamp<T>(low, high), add(add) {}
    // composition, rhs is applied first, *this is applied after
    OffsetClamp operator*(OffsetClamp rhs) const {
        auto cl = Clamp<T>::operator*(Clamp<T>(rhs.low + add, rhs.high + add));
        return OffsetClamp(cl.low, cl.high, add + rhs.add);
    }
    T operator()(T x) const {
        return Clamp<T>::operator()(x + add);
    }
};
