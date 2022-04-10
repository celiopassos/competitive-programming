#ifndef ALGORITHMS_GRAPHS_HUNGARIAN_HPP
#define ALGORITHMS_GRAPHS_HUNGARIAN_HPP

#include "algorithms/common"

// Maintains maximum matching of minimum weight.
template <typename T>
struct Hungarian {
  static constexpr T inf = std::numeric_limits<T>::max();

  int N, M;
  T cost;
  std::vector<int> match;
  std::vector<T> ldual, rdual;
  std::vector<std::vector<T>> C;

  Hungarian(int N, int M) : N(N), M(M), cost(0), match(M, -1), ldual(N), rdual(M), C(N) {
    assert(N <= M);
  }

  void insert(int u, const std::vector<T>& row) {
    C[u] = row;
    ldual[u] = inf;
    for (int v = 0; v < M; ++v) {
      ldual[u] = std::min(ldual[u], C[u][v] - rdual[v]);
    }
    std::vector<T> dmin(M, inf);
    std::vector<int> best(M, -1);
    std::vector<bool> vis(M);
    int last = -1;
    for (int z = u; z != -1; z = match[last]) {
      T delta = inf;
      int next = -1;
      for (int v = 0; v < M; ++v) {
        if (vis[v]) continue;
        T d = C[z][v] - ldual[z] - rdual[v];
        if (d < dmin[v]) {
          dmin[v] = d;
          best[v] = last;
        }
        if (dmin[v] < delta) {
          delta = dmin[v];
          next = v;
        }
      }
      for (int v = 0; v < M; ++v) {
        if (vis[v]) {
          ldual[match[v]] += delta;
          rdual[v] -= delta;
        } else {
          dmin[v] -= delta;
        }
      }
      ldual[u] += delta;
      last = next;
      vis[last] = true;
    }
    for (int v = last; v != -1; v = best[v]) {
      if (best[v] == -1) {
        match[v] = u;
      } else {
        int z = match[best[v]];
        cost -= C[z][best[v]];
        match[v] = z;
      }
      cost += C[match[v]][v];
    }
  }
};

#endif  // ALGORITHMS_GRAPHS_HUNGARIAN_HPP
