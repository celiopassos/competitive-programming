template<typename T>
struct M1
{
    using Type = T;
    inline const static T Id = 0;
    static T op(const T& x, const T& y) { return x + y; }
};

template<typename Monoid>
class PersistentST
{
private:
    using M = Monoid;
    using T = typename Monoid::Type;
    const int n;
    vector<T> st;
    vector<int> left, right, root, last;
    int create(int rt)
    {
        left.push_back(-1), right.push_back(-1);
        last.push_back(rt), st.push_back(M::Id);
        return size(st) - 1;
    }
    int copy(int p, int rt)
    {
        if (p != -1 && rt == last[p]) return p;

        int q = create(rt);

        if (p == -1) return q;

        st[q] = st[p], left[q] = left[p], right[q] = right[p];

        return q;
    }
    void modify(int p, int l, int r, int pos, T value)
    {
        if (l == r) st[p] = value;
        else
        {
            int m = l + (r - l) / 2;

            if (pos <= m) modify(left[p] = copy(left[p], last[p]), l, m, pos, value);

            else modify(right[p] = copy(right[p], last[p]), m + 1, r, pos, value);

            st[p] = M::op(
                left[p] != -1 ? st[left[p]] : M::Id,
                right[p] != -1 ? st[right[p]] : M::Id
            );
        }
    }
    T query(int p, int l, int r, int ql, int qr)
    {
        if (p == -1 || r < ql || qr < l) return M::Id;

        if (ql <= l && r <= qr) return st[p];

        int m = l + (r - l) / 2;

        T resl = query(left[p], l, m, ql, qr);
        T resr = query(right[p], m + 1, r, ql, qr);

        return M::op(resl, resr);
    }
    void build(int p, int l, int r, const vector<T>& a)
    {
        if (l == r) st[p] = a[l];
        else
        {
            int m = l + (r - l) / 2;

            left[p] = create(0), right[p] = create(0);

            build(left[p], l, m, a), build(right[p], m + 1, r, a);

            st[p] = M::op(st[left[p]], st[right[p]]);
        }
    }
public:
    PersistentST(int n) : n(n), root(1, create(0)) { }
    PersistentST(const vector<T>& a) : PersistentST(size(a))
    {
        build(0, 0, n - 1, a);
    }
    int duplicate(int version)
    {
        root.push_back(copy(root[version], size(root)));
        return size(root) - 1;
    }
    void modify(int version, int pos, T value) // modifies version in place
    {
        assert(version < size(root));
        modify(root[version], 0, n - 1, pos, value);
    }
    T query(int version, int l, int r)
    {
        return query(root[version], 0, n - 1, l, r);
    }
};
