struct PartitionMatroid {
    vector<int> cap, color, d;
    PartitionMatroid(const vector<int>& cap, const vector<int>& color) : cap(cap), color(color), d(size(cap)) {}
    void build(const vector<int>& I) {
        fill(begin(d), end(d), 0);
        for (auto u : I) {
            ++d[color[u]];
        }
    }
    bool oracle(int u) const {
        return d[color[u]] < cap[color[u]];
    }
    bool oracle(int u, int v) const {
        return color[u] == color[v] || oracle(v);
    }
};
