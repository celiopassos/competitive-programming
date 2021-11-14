template<int K, int32_t mod>
struct Hash {
    inline static const std::array<int64_t, K> x = [](){
        std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
        std::array<int64_t, K> y;
        std::uniform_int_distribution<int64_t> unif(1, mod - 1);
        for (int i = 0; i < K; ++i) {
            y[i] = unif(rng);
        }
        return y;
    }(), xinv = [](){
        std::array<int64_t, K> y;
        for (int i = 0; i < K; ++i) {
            y[i] = 1;
            for (int64_t p = mod - 2, a = x[i]; p; p >>= 1) {
                if (p & 1) {
                    y[i] = y[i] * a % mod;
                }
                a = a * a % mod;
            }
        }
        return y;
    }();
    std::array<int64_t, K> xp, xpinv, hash;
    Hash() {
        std::fill(xp.begin(), xp.end(), 1);
        std::fill(xpinv.begin(), xpinv.end(), 1);
        std::fill(hash.begin(), hash.end(), 0);
    }
    Hash(int64_t c) : xp(x), xpinv(xinv) {
        std::fill(hash.begin(), hash.end(), c);
    }
    Hash& operator+=(const Hash& rhs) {
        for (int i = 0; i < K; ++i) {
            xp[i] = xp[i] * rhs.xp[i] % mod;
            xpinv[i] = xpinv[i] * rhs.xpinv[i] % mod;
            hash[i] = (rhs.xp[i] * hash[i] + rhs.hash[i]) % mod;
        }
        return *this;
    }
    Hash& operator-=(const Hash& rhs) {
        return *this += -rhs;
    }
    Hash operator+(const Hash& rhs) const {
        return Hash(*this) += rhs;
    }
    Hash operator-(const Hash& rhs) const {
        return Hash(*this) -= rhs;
    }
    Hash operator+() const {
        return *this;
    }
    Hash operator-() const {
        auto res = *this;
        for (int i = 0; i < K; ++i) {
            res.hash[i] = (mod - xpinv[i]) * hash[i] % mod;
            std::swap(res.xp[i], res.xpinv[i]);
        }
        return res;
    }
    Hash power(int64_t p) const {
        Hash h = *this;
        if (p < 0) p *= -1, h = -h;
        Hash res;
        while (p) {
            if (p & 1) res = res + h;
            h += h, p >>= 1;
        }
        return res;
    }
    bool operator==(const Hash& rhs) const {
        return hash == rhs.hash && xp == rhs.xp;
    }
    bool operator!=(const Hash& rhs) const {
        return !(*this == rhs);
    }
    struct custom_hash {
        size_t operator()(const Hash& h) const {
            size_t res = 0;
            for (int i = 0; i < K; ++i) {
                res = res * mod + h.hash[i];
            }
            return res;
        }
    };
};
