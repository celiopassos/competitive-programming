#ifndef ALGORITHMS_MATHEMATICS_MATROIDS_PARTITION_MATROID_HPP
#define ALGORITHMS_MATHEMATICS_MATROIDS_PARTITION_MATROID_HPP

#include "algorithms/common"

struct PartitionMatroid {
  std::vector<int> cap, color, d;

  PartitionMatroid(const std::vector<int>& cap, const std::vector<int>& color)
      : cap(cap), color(color), d(cap.size()) {}

  void build(const std::vector<int>& I) {
    std::fill(d.begin(), d.end(), 0);
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

#endif  // ALGORITHMS_MATHEMATICS_MATROIDS_PARTITION_MATROID_HPP
