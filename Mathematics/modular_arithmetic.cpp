template<long long P>
struct Z {
    long long x;
    Z() : x(0) {}
    Z(long long x_) {
        x = x_ % P;
        if (x < 0) x += P;
    }
    Z& operator+=(Z rhs) {
        x += rhs.x;
        if (x >= P) x -= P;
        return *this;
    }
    Z& operator-=(Z rhs) {
        x -= rhs.x;
        if (x < 0) x += P;
        return *this;
    }
    Z& operator*=(Z rhs) {
        x = x * rhs.x % P;
        return *this;
    }
    Z& operator/=(Z rhs) {
        return *this *= rhs.power(-1);
    }
    Z power(long long p) const {
        p %= P - 1;
        if (p < 0) p += P - 1;
        Z res = 1;
        for (Z y = *this; p; p >>= 1, y *= y) if (p & 1) res *= y;
        return res;
    }
    Z operator-() const {
        return Z() - *this;
    }
    bool operator==(Z rhs) const { return x == rhs.x; }
    bool operator!=(Z rhs) const { return x != rhs.x; }
    bool operator<(Z rhs) const { return x < rhs.x; }
    friend Z operator+(Z lhs, Z rhs) { return lhs += rhs; }
    friend Z operator-(Z lhs, Z rhs) { return lhs -= rhs; }
    friend Z operator*(Z lhs, Z rhs) { return lhs *= rhs; }
    friend Z operator/(Z lhs, Z rhs) { return lhs /= rhs; }
    friend ostream& operator<<(ostream& out, Z a) { return out << a.x; }
    friend istream& operator>>(istream& in, Z& a) {
        long long x;
        in >> x;
        a = Z(x);
        return in;
    }
    inline static const Z X = [](){
        uniform_int_distribution<long long> unif(1, P - 1);
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        return unif(rng);
    }(), Xinv = 1 / X;
};
