struct CentroidDecomposition {
  struct Info {
    int root, dist, bucket;
    Info(int root, int dist, int bucket) :
      root(root), dist(dist), bucket(bucket) {}
  };
  const std::vector<std::vector<int>>& E;
  int N, num_buckets = 0;
  std::vector<bool> dead;
  std::vector<int> size, level;
  std::vector<std::vector<Info>> info;
  int find_centroid(int u, int p, int n) const {
    for (auto v : E[u]) {
      if (v == p || dead[v]) continue;
      if (size[v] > n / 2) {
        return find_centroid(v, u, n);
      }
    }
    return u;
  }
  void dfs(int u, int p) {
    size[u] = 1;
    for (auto v : E[u]) {
      if (v == p || dead[v]) continue;
      info[v].push_back(info[u].back());
      ++info[v].back().dist;
      dfs(v, u);
      size[u] += size[v];
    }
  }
  CentroidDecomposition(const std::vector<std::vector<int>>& E) :
    E(E), N(E.size()), dead(N), size(N), level(N), info(N)
  {
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int rt = q.front();
      q.pop();
      dead[rt] = true;
      for (auto v : E[rt]) {
        if (dead[v]) continue;
        info[v].emplace_back(rt, 1, num_buckets++);
        dfs(v, rt);
        int nrt = find_centroid(v, rt, size[v]);
        level[nrt] = level[rt] + 1;
        q.push(nrt);
      }
    }
  }
  int parent(int u) const {
    return info[u].empty() ? -1 : info[u].back().root;
  }
  int lca(int u, int v) const {
    while (level[u] > level[v]) {
      u = parent(u);
    }
    while (level[v] > level[u]) {
      v = parent(v);
    }
    while (u != v) {
      u = parent(u);
      v = parent(v);
    }
    return u;
  }
  int dist(int u, int v) const {
    int w = lca(u, v);
    int res = 0;
    for (auto x : {u, v}) {
      if (level[w] < level[x]) {
        res += info[x][level[w]].dist;
      }
    }
    return res;
  }
};
