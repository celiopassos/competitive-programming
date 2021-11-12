template<typename T>
T extended_gcd(T a, T b, T& x, T& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    } else {
        T q = b / a, r = b % a;
        T g = extended_gcd(r, a, y, x);
        x -= q * y;
        return g;
    }
}
