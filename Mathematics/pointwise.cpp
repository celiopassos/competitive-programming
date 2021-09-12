template<typename T, int K>
struct Pointwise : public array<T, K> {
    using P = Pointwise;
    Pointwise(T value = 0) {
        fill(*this.begin(), *this.end(), value);
    }
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
    friend P operator+(P lhs, const P& rhs) {
        return lhs += rhs;
    }
    friend P operator-(P lhs, const P& rhs) {
        return lhs -= rhs;
    }
    friend P operator*(P lhs, const P& rhs) {
        return lhs *= rhs;
    }
    friend P operator/(P lhs, const P& rhs) {
        return lhs /= rhs;
    }
    P operator+() const {
        return *this;
    }
    P operator-() const {
        return P(T(0)) -= *this;
    }
    P power(long long p) const {
        P res;
        for (int j = 0; j < K; ++j) res[j] = (*this)[j].power(p);
        return res;
    }
    inline static const Pointwise X = [](){
        uniform_int_distribution<long long> unif(1, numeric_limits<long long>::max());
        Pointwise X;
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (int j = 0; j < K; ++j) X[j] = T(unif(rng));
        return X;
    }(), Xinv = P(1) / X;
    P& operator<<=(long long p) {
        return *this *= X.power(p);
    }
    P& operator>>=(long long p) {
        return *this *= Xinv.power(p);
    }
    P operator<<(long long p) const {
        return *this * X.power(p);
    }
    P operator>>(long long p) const {
        return *this * Xinv.power(p);
    }
};
