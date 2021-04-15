// K >= centroid tree height, or simply floor(log(n))

template<int K>
class CentroidDecomposition {
private:
    const int n;
    const vector<vector<int>>& E;

    vector<int> parent, weight, vis, level;
    vector<array<int, K + 1>> dist;

    int dfs(int u, int p, int h) {
        if (h != -1) dist[u][h] = dist[p][h] + 1;

        weight[u] = 1;

        for (auto v : E[u]) if (not vis[v] && v != p)
            weight[u] += dfs(v, u, h);

        return weight[u];
    }
    int find_centroid(int u, int p, int cut) {
        for (auto v : E[u])
            if (not vis[v] && v != p && weight[v] > cut)
                return find_centroid(v, u, cut);

        return u;
    }
    void build(int u, int p) {
        int total = dfs(u, p, p == -1 ? -1 : level[p]);
        int centroid = find_centroid(u, p, total / 2);

        if (p != -1) level[centroid] = level[p] + 1;

        parent[centroid] = p, vis[centroid] = 1;
        dist[centroid][level[centroid]] = 0;

        for (auto v : E[centroid]) if (not vis[v]) build(v, centroid);
    }
public:
    CentroidDecomposition(const vector<vector<int>>& E) :
        n((int)size(E)), E(E), parent(n), weight(n), vis(n), level(n), dist(n) {
        build(0, -1);
    }
    int operator[](int u) const {
        return parent[u];
    }
    int getlevel(int u) const {
        return level[u];
    }
    int lca(int u, int v) const // centroid lca, not tree lca {
        if (level[u] < level[v]) swap(u, v);

        while (level[u] > level[v]) u = parent[u];

        while (u != v) u = parent[u], v = parent[v];

        return u;
    }
    int distance(int u, int v) const {
        int w = lca(u, v);

        return dist[u][level[w]] + dist[v][level[w]];
    }
};
