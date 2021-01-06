template<typename T>
struct G1
{
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static T inv(const T& x) { return -x; }
    static bool cmp(const T& x, const T& y) { return x < y; }
};

template<typename Group>
class BIT
{
private:
    using G = Group;
    using T = typename G::Type;
    int b(int p) { return p & (-p); }
    const int n, h;
    vector<T> ft;
    T query(int p)
    {
        T res = G::Id;
        for (int i = p; i >= 1; i -= b(i)) res = G::op(ft[i], res);
        return res;
    }
public:
    BIT(int n) : n(n), h(31 - __builtin_clz(n)), ft(n + 1, G::Id) { }
    BIT(const vector<T>& a) : BIT(size(a))
    {
        for (int i = 1; i <= n; ++i) ft[i] = G::op(ft[i - 1], a[i - 1]);
        for (int i = n; i >= 1; --i) ft[i] = G::op(G::inv(ft[i - b(i)]), ft[i]);
    }
    T query(int l, int r) { return G::op(G::inv(query(l)), query(r + 1)); }
    void update(int p, T value)
    {
        for (int i = p + 1; i <= n; i += b(i)) ft[i] = G::op(ft[i], value);
    }
    int lower_bound(T value) // first r such that G::cmp(query(0, r), value) == false
    {
        T prefix = G::Id;
        int pos = 0;
        for (int x = h; x >= 0; --x)
        {
            if (pos + (1 << x) <= n && G::cmp(G::op(prefix, ft[pos + (1 << x)]), value) == true)
            {
                pos += 1 << x;
                prefix = G::op(prefix, ft[pos]);
            }
        }
        return pos;
    }
};
