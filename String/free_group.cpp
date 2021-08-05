template<typename T>
struct FreeGroup {
    T shift, inv_shift, hash;
    FreeGroup() : shift(1), inv_shift(1), hash(0) { }
    FreeGroup(T shift, T inv_shift, T hash) : shift(shift), inv_shift(inv_shift), hash(hash) {}
    FreeGroup(long long c) : shift(T::X), inv_shift(T::Xinv), hash(c) { }
    template<typename Iterator>
    FreeGroup(Iterator first, Iterator last) : FreeGroup() {
        while (first != last) {
            *this += *first;
            ++first;
        }
    }
    FreeGroup& operator+=(const FreeGroup& rhs) {
        shift *= rhs.shift;
        inv_shift = inv_shift * rhs.inv_shift;
        hash = rhs.shift * hash + rhs.hash;
        return *this;
    }
    FreeGroup& operator-=(const FreeGroup& rhs) { return *this += -rhs; }
    FreeGroup operator+(const FreeGroup& rhs) const { return FreeGroup(*this) += rhs; }
    FreeGroup operator-(const FreeGroup& rhs) const { return FreeGroup(*this) -= rhs; }
    FreeGroup operator+() const { return *this; }
    FreeGroup operator-() const {
        return FreeGroup(inv_shift, shift, -inv_shift * hash);
    }
    FreeGroup power(long long p) const {
        FreeGroup x = *this;
        if (p < 0) p *= -1, x = -x;
        FreeGroup res;
        while (p) {
            if (p & 1) res = res + x;
            x += x, p >>= 1;
        }
        return res;
    }
    bool operator<(const FreeGroup& rhs) const { return pair(shift, hash) < pair(rhs.shift, rhs.hash); }
    bool operator==(const FreeGroup& rhs) const { return shift == rhs.shift && hash == rhs.hash; }
    bool operator!=(const FreeGroup& rhs) const { return not (*this == rhs); }
};
