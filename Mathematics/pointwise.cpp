const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(FIXED_RANDOM);

template<typename T, int K>
struct Pointwise : public array<T, K> {
    using P = Pointwise;
    Pointwise(T value = 0) { fill(begin(*this), end(*this), value); }
    P& operator+=(const P& rhs) {
        for (int j = 0; j < K; ++j) (*this)[j] += rhs[j];
        return *this;
    }
    P& operator-=(const P& rhs) {
        for (int j = 0; j < K; ++j) (*this)[j] -= rhs[j];
        return *this;
    }
    P& operator*=(const P& rhs) {
        for (int j = 0; j < K; ++j) (*this)[j] *= rhs[j];
        return *this;
    }
    P& operator/=(const P& rhs) {
        for (int j = 0; j < K; ++j) (*this)[j] /= rhs[j];
        return *this;
    }
    friend P operator+(P lhs, const P& rhs) { return lhs += rhs; }
    friend P operator-(P lhs, const P& rhs) { return lhs -= rhs; }
    friend P operator*(P lhs, const P& rhs) { return lhs *= rhs; }
    friend P operator/(P lhs, const P& rhs) { return lhs /= rhs; }
    P operator+() const { return *this; }
    P operator-() const { return P(T(0)) -= *this; }
    P power(ll p) const {
        P res;
        for (int j = 0; j < K; ++j) res[j] = (*this)[j].power(p);
        return res;
    }
    // X 'indeterminate' for polynomial hashing
    // probability of collision when comparing two instances = (degree of difference / mod)^K
    inline static const Pointwise X = [](){
        uniform_int_distribution<ll> unif(1, numeric_limits<ll>::max());
        Pointwise X;
        for (int j = 0; j < K; ++j) X[j] = T(unif(rng));
        return X;
    }();
    P& operator>>=(ll p) { return *this *= X.power(p); }
    P operator>>(ll p) const { return *this * X.power(p); }
};
