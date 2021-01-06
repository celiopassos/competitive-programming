class DSU
{
private:
    vector<int> p, rk;
    int components;
public:
    DSU(int n) : p(n, 0), rk(n, 0), components(n)
    {
        for (int i = 0; i < n; ++i) p[i] = -1;
    }
    int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
    int find_size(int i) { return -p[find(i)]; }
    int (size)() const { return components; }
    void unite(int i, int j)
    {
        int x = find(i), y = find(j);
        if (rk[x] < rk[y]) swap(x, y);
        if (x != y)
        {
            --components;
            p[x] += p[y], p[y] = x;
            rk[x] += (rk[x] == rk[y]);
        }
    }
};
