template<typename T>
struct G1
{
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
    static T inv(const T& x) { return -x; }
    static bool cmp(const T& x, const T& y) { return x < y; }
};

int b(int p) { return p & (-p); }

template<typename Group>
class BIT
{
private:
    using G = Group;
    using T = typename G::Type;
    const int n, h;
    vector<T> ft;
    T query(int p)
    {
        T res = G::Id;
        for (; p; p -= b(p)) res = G::op(ft[p], res);
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
        for (++p; p <= n; p += b(p)) ft[p] = G::op(ft[p], value);
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
