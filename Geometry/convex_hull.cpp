// counter-clockwise order
template<typename T>
vector<complex<T>> convex_hull(vector<complex<T>> pts) {
    sort(pts.begin(), pts.end(), lex_cmp<T>), pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 1) return pts;
    vector<complex<T>> upper(pts.size()), lower(pts.size());
    int k = 0, l = 0;
    for (auto p : pts) {
        while (k > 1 && not cw(upper[k - 2], upper[k - 1], p)) --k;
        while (l > 1 && not ccw(lower[l - 2], lower[l - 1], p)) --l;
        upper[k++] = lower[l++] = p;
    }
    upper.resize(k - 1), lower.resize(l);
    reverse(upper.begin(), upper.end());
    lower.insert(lower.end(), upper.begin(), upper.end() - 1);
    return lower;
}
