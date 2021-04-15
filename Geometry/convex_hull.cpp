template<typename T>
vector<complex<T>> convex_hull(vector<complex<T>> pts) {
    sort(all(pts), lex_cmp<T>), pts.erase(unique(all(pts)), end(pts));

    int n = (int)size(pts);
    if (n == 1) return pts;

    vector<complex<T>> up(n), down(n);
    int k = 1, j = 1;

    auto p = pts[0], q = pts[n - 1];
    up[0] = p, down[0] = p;

    for (int i = 1; i < n; ++i) {
        if (i == n - 1 || cw(p, pts[i], q)) {
            while (k > 1 && not cw(up[k - 2], up[k - 1], pts[i])) --k;
            up[k++] = pts[i];
        }
        if (i == n - 1 || ccw(p, pts[i], q)) {
            while (j > 1 && not ccw(down[j - 2], down[j - 1], pts[i])) --j;
            down[j++] = pts[i];
        }
    }

    reverse(begin(up), begin(up) + k);
    copy(begin(up), begin(up) + k - 1, begin(down) + j - 1);
    down.resize(k + j - 2);

    return down;
}
