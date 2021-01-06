template<typename T, bool memory_optimized = false>
struct DSU
{
private:
    vector<int> p, rk;
    vector<T> aggregate;
    const function<void(T&, T&)> merger;
    int components;
public:
    DSU(int n, T value, auto merger) : DSU(n, vector<T>(n, value), merger) { }
    DSU(const vector<T>& agg, auto merger) :
        p(size(agg)), rk(size(agg), 0), aggregate(agg), merger(merger), components(size(agg))
    {
        iota(all(p), 0);
    }
    int find(int u) { return p[u] == u ? u : p[u] = find(p[u]); }
    T& query(int u) { return aggregate[find(u)]; }
    int (size)() const { return components; }
    void unite(int u, int v)
    {
        u = find(u), v = find(v);
        if (rk[u] < rk[v]) swap(u, v);
        if (u != v)
        {
            rk[u] += (rk[u] == rk[v]), p[v] = p[u];
            merger(aggregate[u], aggregate[v]);
            if (memory_optimized) aggregate[v].~T();
        }
    }
};
