template<typename T, typename... Args>
auto ternary_search(T l, T r, T eps, auto&& f, Args... args)
{
    while (r - l > eps)
    {
        T m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
        if (f(m1, args...) > f(m2, args...)) l = m1;
        else r = m2;
    }
    T c = l;
    for (T x = c + 1; x <= r; ++x)
        if (f(x, args...) < f(c, args...)) c = x;
    return pair(f(c, args...), c);
}
