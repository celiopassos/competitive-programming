class DSU
{
private:
    vector<int> p;
    int components;
    stack<pair<int&, int>> snapshots;
    void save(int& x) { snapshots.push(pair<int&, int>(x, x)); }
public:
    DSU(int n) : p(n), components(n)
    {
        for (int u = 0; u < n; ++u) p[u] = -1;
    }
    int find(int u) const
    {
        while (p[u] >= 0) u = p[u];
        return u;
    }
    int find_size(int u) const { return -p[find(u)]; }
    int (size)() const { return components; }
    void rollback()
    {
        for (int t = 0; t < 3; ++t)
        {
            snapshots.top().first = snapshots.top().second;
            snapshots.pop();
        }
    }
    void unite(int u, int v)
    {
        int x = find(u), y = find(v);
        if (-p[x] < -p[y]) swap(x, y);
        save(components), save(p[x]), save(p[y]);
        if (x != y) components -= 1, p[x] += p[y], p[y] = x;
    }
};
