#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

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

int main()
{ _
    exit(0);
}
