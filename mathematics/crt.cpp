template<typename T>
struct crt_t {
    T a, mod;
    crt_t() : a(0), mod(1) {}
    crt_t(T a_, T mod_) : a(a_), mod(mod_) {
        a %= mod;
        if (a < 0) a += mod;
    }
    crt_t operator+(crt_t rhs) const {
        T x, y;
        T g = extended_gcd(mod, rhs.mod, x, y);
        if (a == -1 || rhs.a == -1 || (a - rhs.a) % g) {
            crt_t res;
            res.a = -1;
            return res;
        }
        T lcm = mod / g * rhs.mod;
        return crt_t(a + (rhs.a - a) / g * mod * x, lcm);
    }
};
