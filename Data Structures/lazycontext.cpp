using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// query: range sum
// update: range add
//
// F1(x) will add x on the range being updated

template<typename T>
struct F1
{
    inline static T Tid = T(0);
    inline static F1 Fid = F1(0);
    T add;
    inline explicit F1(T add) : add(add) {}
    void apply(T& old, int L, int R) const
    {
        old = old + add * (R - L + 1);
    }
    void compose(const F1& op, int L, int R)
    {
        add += op.add;
    }
    bool operator==(const F1& op) const { return add == op.add; }
    static T op(const T& x, const T& y)
    {
        return x + y;
    }
};

// query: range sum
// update: range assigment
//
// F2(x) will set all values in the range to x
//
// if you to set some value to LINF, you'll need
// to change the LINF below to some other value

template<typename T>
struct F2
{
    inline static T Tid = T(0);
    inline static F2 Fid = F2(T(LINF));
    T value;
    explicit F2(T value) : value(value) {}
    void apply(T& old, int L, int R) const
    {
        if (*this == Fid) return;
        old = (R - L + 1) * value;
    }
    void compose(const F2& op, int L, int R)
    {
        if (op == Fid) return;
        value = op.value;
    }
    bool operator==(const F2& op) const { return value == op.value; }
    static T op(const T& x, const T& y)
    {
        return x + y;
    }
};

// query: range sum
// update: add linear function on range
//
// F3(a, b) will add a * i + b on index i
// for every i in the range being updated
//
// may work badly with negative indices

template<typename T>
struct F3
{
    inline static T Tid = T(0);
    inline static F3 Fid = F3(0, 0);

    T a, b;

    explicit F3(T a, T b) : a(a), b(b) {}

    static T ap(T n) { return n * (n + 1) / 2; }

    void apply(T& old, int L, int R) const
    {
        old += a * (ap(R) - ap(L - 1)) + b * (R - (L - 1));
    }
    void compose(const F3& op, int L, int R)
    {
        a += op.a, b += op.b;
    }
    bool operator==(const F3& op) const
    {
        return a == op.a && b == op.b;
    }
    static T op(const T& x, const T& y)
    {
        return x + y;
    }
};
