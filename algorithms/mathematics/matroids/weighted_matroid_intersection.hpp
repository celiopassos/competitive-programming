#ifndef ALGORITHMS_MATHEMATICS_MATROIDS_WEIGHTED_MATROID_INTERSECTION_HPP
#define ALGORITHMS_MATHEMATICS_MATROIDS_WEIGHTED_MATROID_INTERSECTION_HPP

#include <algorithm>
#include <utility>
#include <vector>

template <typename X, typename Y>
std::pair<X, Y> neg(std::pair<X, Y> p) {
  return {-p.first, -p.second};
}

// Assumes w >= 0 (modify to SPFA otherwise).
template <typename T, typename Matroid1, typename Matroid2>
std::vector<int> weighted_matroid_intersection(int N, std::vector<T> w, Matroid1& M1, Matroid2& M2) {
  std::vector<bool> b(N), target(N);
  std::vector<int> I[2], from(N);
  std::vector<std::array<T, 2>> p(N);
  std::vector<std::pair<T, int>> d(N);
  std::vector<std::pair<std::pair<T, int>, int>> heap;
  auto check_edge = [&](int u, int v) {
    return (b[u] && M1.oracle(u, v)) || (b[v] && M2.oracle(v, u));
  };
  while (true) {
    I[0].clear(), I[1].clear();
    for (int u = 0; u < N; ++u) {
      I[b[u]].push_back(u);
    }
    M1.build(I[1]), M2.build(I[1]);
    std::fill(d.begin(), d.end(), std::pair(std::numeric_limits<T>::max(), std::numeric_limits<int>::max()));
    std::fill(target.begin(), target.end(), false);
    std::fill(from.begin(), from.end(), -1);
    for (auto u : I[0]) {
      target[u] = M2.oracle(u);
      if (M1.oracle(u)) {
        d[u] = {w[u] + p[u][0] - p[u][1], 0};
        heap.emplace_back(neg(d[u]), u);
      }
    }
    std::make_heap(heap.begin(), heap.end());
    bool converged = true;
    while (!heap.empty()) {
      auto [du, u] = heap[0];
      std::pop_heap(heap.begin(), heap.end());
      heap.pop_back();
      if (neg(du) != d[u]) continue;
      if (target[u]) {
        converged = false;
        heap.clear();
        for (int v = 0; v < N; ++v) {
          T cost = w[v] + p[v][b[v]] - p[v][!b[v]];
          // assert(cost >= 0);
          // assert(d[v].first - cost >= 0);
          p[v][b[v]] += std::min(d[v].first - cost, d[u].first);
          p[v][!b[v]] += std::min(d[v].first, d[u].first);
        }
        for (int v = u; v != -1; v = from[v]) {
          b[v] = !b[v];
          w[v] *= -1;
        }
        break;
      }
      for (auto v : I[!b[u]]) {
        if (!check_edge(u, v)) continue;
        // assert(p[u][!b[u]] - p[v][!b[u]] >= 0);
        // assert(w[v] + p[v][!b[u]] - p[v][b[u]] >= 0);
        std::pair<T, int> nd(d[u].first + w[v] + p[u][!b[u]] - p[v][b[u]], d[u].second + 1);
        if (nd < d[v]) {
          from[v] = u;
          d[v] = nd;
          heap.emplace_back(neg(d[v]), v);
          std::push_heap(heap.begin(), heap.end());
        }
      }
    }
    if (converged) break;
  }
  return I[1];
}

#endif  // ALGORITHMS_MATHEMATICS_MATROIDS_WEIGHTED_MATROID_INTERSECTION_HPP
