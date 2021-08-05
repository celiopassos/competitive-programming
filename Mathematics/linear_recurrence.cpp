template<typename T>
T one_coeff(vector<T> p, vector<T> q, long long n) {
    int d = (int)p.size();
    for (; n > 0; n >>= 1) {
        auto qsgn = q;
        for (int i = 1; i <= d; i += 2) qsgn[i] *= -1;
        auto u = p * qsgn, v = q * qsgn;
        for (int i = 0, b = (n & 1 ? 1 : 0); i < d; ++i) {
            p[i] = u[i << 1 | b];
            q[i] = v[i << 1];
        }
        q[d] = v[d << 1];
    }
    return p[0] / q[0];
}
// given the linear recurrence u[i+d] = c[0]u[i] + ... + c[d-1]u[i+d-1]
// and the initial values u[0], ..., u[d-1], finds u[n]
// O(convolution(d) * log(n))
template<typename T>
T solve(vector<T> c, vector<T> u, long long n) {
    int d = (int)c.size();
    vector<T> q(d + 1, 0);
    q[0] = 1;
    for (int i = 0; i < d; ++i) q[d - i] -= c[i];
    auto p = u * q;
    p.resize(d);
    return one_coeff(p, q, n);
}
