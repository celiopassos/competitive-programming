// returns minimum x such that a^x = b (-1 if there is none)
int64_t discrete_log(int64_t a, int64_t b, int64_t mod) {
    assert(0 <= a < mod);
    assert(0 <= b < mod);
    int64_t k = 1, add = 0;
    while (true) {
        int64_t g = std::gcd(a, mod);
        if (g == 1) break;
        if (b == k) return add;
        if (b % g) return -1;
        b /= g;
        mod /= g;
        k = k * a / g % mod;
        ++add;
    }
    int64_t d = 1 + sqrtl(mod);
    std::unordered_map<int64_t, int> small;
    int64_t x = 1;
    for (int i = 1; i <= d; ++i) {
        x = x * a % mod;
        small[b * x % mod] = i;
    }
    int64_t y = k;
    for (int i = 1; i <= d; ++i) {
        y = y * x % mod;
        if (small.count(y)) {
            return i * d - small[y] + add;
        }
    }
    return -1;
}
