// T domain, Y image
template<typename T, typename Y, typename F, typename... Args>
pair<Y, T> ternary_search_float(T l, T r, int it, F& f, Args... args) {
    for (int i = 0; i < it; ++i) {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        f(m1, args...) > f(m2, args...) ? l = m1 : r = m2;
    }
    return pair(f(l, args...), l);
}
template<typename T, typename Y, typename F, typename... Args>
pair<Y, T> ternary_search_int(T l, T r, F& f, Args... args) {
    while (l < r) {
        T m = l + (r - l) / 2;
        f(m, args...) > f(m + 1, args...) ? l = m + 1 : r = m;
    }
    return pair(f(l, args...), l);
}
