struct ColorfulMatroid {
    vector<int> color;
    vector<bool> on;
    int N;
    ColorfulMatroid(const vector<int>& color_) : color(color_), N((int)size(color)) {
        // coordinate compression
        auto values = color;
        sort(begin(values), end(values));
        values.erase(unique(begin(values), end(values)), end(values));
        for (int u = 0; u < N; ++u) {
            color[u] = (int)(lower_bound(begin(values), end(values), color[u]) - begin(values));
        }
        on.resize(size(values));
    }
    void build(const vector<int>& I) {
        fill(begin(on), end(on), false);
        for (auto u : I) {
            assert(on[color[u]] == false);
            on[color[u]] = true;
        }
    }
    bool oracle(int u) const {
        return not on[color[u]];
    }
    bool oracle(int u, int v) const {
        return oracle(v) || color[u] == color[v];
    }
};
