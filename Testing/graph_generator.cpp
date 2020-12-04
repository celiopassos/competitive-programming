#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;

const int L = 1e7, R = 1e9;

uniform_int_distribution<int> unif(L, R);

// trees will most likely have O(log(n)) height
// also, connected graphs will have O(log(n)) diameter
// number of edges is not exact, specially with small graphs
// make sure to relabel, catches stupid bugs
// 0-based

auto tree_generator(int n)
{
    vector edges(0, pair(0, 0));

    for (int u = 1; u < n; ++u)
        edges.emplace_back(unif(rng) % u, u);

    return edges;
}

auto graph_generator(int n, int m)
{
    vector edges(0, pair(0, 0));

    for (int j = 0; j < m; ++j)
    {
        int u = unif(rng) % n, v = unif(rng) % n;
        if (u == v) continue;
        if (u > v) swap(u, v);
        edges.emplace_back(u, v);
    }

    sort(all(edges)), edges.erase(unique(all(edges)), end(edges));

    return edges;
}

auto connected_graph_generator(int n, int m)
{
    assert(m >= n - 1);

    auto tree = tree_generator(n);

    auto edges = graph_generator(n, m - (n - 1));

    edges.insert(end(edges), all(tree));

    sort(all(edges)), edges.erase(unique(all(edges)), end(edges));

    return edges;
}

void relabel(int n, auto& edges)
{
    vector label(n, 0); iota(all(label), 0);

    shuffle(all(label), rng);

    for (auto& [u, v] : edges)
    {
        u = label[u], v = label[v];
        if (u > v) swap(u, v);
    }
}

int main()
{ _
    exit(0);
}
