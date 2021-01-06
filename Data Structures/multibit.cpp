template <typename T, int... Args>
struct BIT
{
    static const T id = T();
    static T combine(T x, T y) { return x + y; }
    static T inv(T x) { return -x; }
    T value = id;
    void modify(T value) { this->value = value; }
    int query() { return value; }
};

template <typename T, int N, int... Ns>
class BIT<T, N, Ns...>
{
private:
    using B = BIT<T>;
    array<BIT<T, Ns...>, N> ft;
    template<typename... Args>
    T prefix(int p, Args... args)
    {
        T res = B::id;
        for (int i = p; i >= 0; i = (i & (i + 1)) - 1)
            res = B::combine(res, ft[i].query(args...));
        return res;
    }
public:
    template<typename... Args>
    void modify(int p, Args... args)
    {
        for (int i = p; i <= N; i = i | (i + 1))
            ft[i].update(args...);
    }
    template<typename... Args>
    T query(int l, int r, Args... args)
    {
        if (l == 0) return prefix(r, args...);
        return B::combine(B::inv(prefix(l - 1, args...)), prefix(r, args...));
    }
};
