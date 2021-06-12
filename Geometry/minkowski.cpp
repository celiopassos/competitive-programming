// minkowski sum
template<typename T>
vector<complex<T>> operator+(vector<complex<T>> P, vector<complex<T>> Q) {
    if (empty(P)) return Q;
    if (empty(Q)) return P;
    rotate(begin(P), min_element(begin(P), end(P), lex_cmp<T>), end(P));
    rotate(begin(Q), min_element(begin(Q), end(Q), lex_cmp<T>), end(Q));
    P.insert(end(P), {P[0], P[1]});
    Q.insert(end(Q), {Q[0], Q[1]});
    vector<complex<T>> res;
    for (size_t i = 0, j = 0; i < size(P) - 2 || j < size(Q) - 2;) {
        res.push_back(P[i] + Q[j]);
        auto t = cross(P[i + 1] - P[i], Q[j + 1] - Q[j]);
        if (t >= 0) ++i;
        if (t <= 0) ++j;
    }
    return res;
}
