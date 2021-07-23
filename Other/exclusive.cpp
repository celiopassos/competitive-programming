// op should map (X, Y) -> Y
template<typename X, typename Y, typename Op>
vector<Y> exclusive(const vector<X>& a, Y Id, Op&& op) {
    int N = (int)size(a);
    vector<Y> res(N, Id);
    for (int b = __lg(N - 1); b >= 0; --b) {
        for (int i = N - 1; i >= 0; --i) {
            res[i] = res[i >> 1];
        }
        for (int i = 0; i < N; ++i) {
            int idx = (i >> b) ^ 1;
            if (idx >= N) continue;
            res[idx] = op(a[i], res[idx]);
        }
    }
    return res;
}
