#ifndef ALGORITHMS_STRINGS_DBF_HPP
#define ALGORITHMS_STRINGS_DBF_HPP

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

struct DBF {
  int N, K;
  std::vector<int> log;
  std::vector<std::vector<int>> p, rank;

  template <typename Iterator>
  DBF(Iterator first, Iterator last)
      : N(last - first), K(1), log(N + 1), p(1, std::vector<int>(N)), rank(p) {
    for (int n = 2; n <= N; ++n) {
      log[n] = 1 + log[n >> 1];
    }
    std::iota(p[0].begin(), p[0].end(), 0);
    std::sort(p[0].begin(), p[0].end(), [&](int i, int j) { return first[i] < first[j]; });
    for (int i = 1; i < N; ++i) {
      rank[0][p[0][i]] = rank[0][p[0][i - 1]] + (first[p[0][i]] != first[p[0][i - 1]]);
    }
    std::vector<int> cnt(N), tmp(N);
    for (int k = 0; (1 << k) < N; ++k, ++K) {
      p.emplace_back(N);
      rank.emplace_back(N);
      for (int i = 0; i < N; ++i) {
        tmp[N - 1 - i] = (p[k][i] + N - (1 << k)) % N;
        ++cnt[rank[k][p[k][i]]];
      }
      std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
      for (auto i : tmp) {
        p[k + 1][--cnt[rank[k][i]]] = i;
      }
      std::fill(cnt.begin(), cnt.end(), 0);
      auto key = [&](int i) { return std::pair(rank[k][i], rank[k][(i + (1 << k)) % N]); };
      for (int i = 1; i < N; ++i) {
        auto& r = rank[k + 1];
        r[p[k + 1][i]] = r[p[k + 1][i - 1]] + (key(p[k + 1][i]) != key(p[k + 1][i - 1]));
      }
    }
  }

  std::pair<int, int> key(int i, int len) const {
    if (len == 0) return {-1, -1};
    int k = log[len];
    return std::pair(rank[k][i], rank[k][(i + len - (1 << k)) % N]);
  };

  bool cmp(std::pair<int, int> S, std::pair<int, int> T) const {
    int lenS = S.second - S.first, lenT = T.second - T.first, min = std::min(lenS, lenT);
    auto keyS = key(S.first, min), keyT = key(T.first, min);
    return keyS != keyT ? keyS < keyT : lenS < lenT;
  }

  // Returns cyclic lcp (assumes cyclic permutations starting from i and j are not equal).
  int lcp_query(int i, int j) const {
    int len = 0;
    for (int k = K - 1; k >= 0; --k) {
      if (rank[k][i] == rank[k][j]) {
        int p = 1 << k;
        len += p;
        i = (i + p) % N;
        j = (j + p) % N;
      }
    }
    return len;
  }
};

#endif  // ALGORITHMS_STRINGS_DBF_HPP
