template<typename T>
struct Clamp {
    static const T inf = numeric_limits<T>::max() / 2;
    T low, high, add;
    Clamp(T low = -inf, T high = +inf, T add = 0) : low(low), high(high), add(add) {}
    // composition, rhs is applied first, *this is applied after
    Clamp operator*(Clamp rhs) const {
        T nadd = add + rhs.add;
        T nlow = std::clamp(rhs.low - rhs.add, low - nadd, high - nadd) + nadd;
        T nhigh = std::clamp(rhs.high - rhs.add, low - nadd, high - nadd) + nadd;
        return Clamp(nlow, nhigh, nadd);
    }
    T operator()(T x) const {
        return std::clamp(x + add, low, high);
    }
};
