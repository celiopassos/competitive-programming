#ifndef ALGORITHMS_GEOMETRY_CONVEX_HULL_HPP
#define ALGORITHMS_GEOMETRY_CONVEX_HULL_HPP

#include <algorithm>
#include <complex>
#include <vector>

// Returns convex hull sorted in counter-clockwise order.
template <typename T>
std::vector<std::complex<T>> convex_hull(std::vector<std::complex<T>> pts) {
  std::sort(pts.begin(), pts.end(), [](auto p, auto q) { return p.x() < q.x(); });
  pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
  if (pts.size() <= 2) return pts;
  std::vector<std::complex<T>> upper(pts.size()), lower(pts.size());
  int k = 0, l = 0;
  for (auto p : pts) {
    while (k > 1 && !cw(upper[k - 2], upper[k - 1], p)) --k;
    while (l > 1 && !ccw(lower[l - 2], lower[l - 1], p)) --l;
    upper[k++] = lower[l++] = p;
  }
  upper.resize(k - 1), lower.resize(l);
  lower.insert(lower.end(), upper.rbegin(), upper.rend() - 1);
  return lower;
}

#endif  // ALGORITHMS_GEOMETRY_CONVEX_HULL_HPP
