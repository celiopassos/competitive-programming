template <typename Iterator>
std::vector<int> sort_cyclic_shifts(Iterator first, Iterator last) {
  int N = last - first;
  std::vector<int> p(N), inv(N), tmp(N), cnt(N);
  std::iota(p.begin(), p.end(), 0);
  std::sort(
      p.begin(), p.end(), [&](int i, int j) { return first[i] < first[j]; });
  inv[p[0]] = 0;
  for (int i = 1; i < N; ++i) {
    inv[p[i]] = inv[p[i - 1]] + (first[p[i]] != first[p[i - 1]] ? 1 : 0);
  }
  for (int shift = 1; shift < N; shift *= 2) {
    std::fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < N; ++i) {
      tmp[N - 1 - i] = (p[i] + N - shift) % N;
      cnt[inv[p[i]]] += 1;
    }
    std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for (auto i : tmp) p[--cnt[inv[i]]] = i;
    auto key = [&](int i) { return std::pair(inv[i], inv[(i + shift) % N]); };
    tmp[p[0]] = 0;
    for (int i = 1; i < N; ++i) {
      tmp[p[i]] = tmp[p[i - 1]] + (key(p[i - 1]) != key(p[i]) ? 1 : 0);
    }
    std::swap(tmp, inv);
  }
  return p;
}
struct SuffixArray {
  int N;
  std::vector<int> p, pos, lcp;
  SuffixArray(std::string S) {
    S.push_back(0);
    N = S.size();
    p = sort_cyclic_shifts(S.begin(), S.end());
    pos.resize(N);
    lcp.resize(N);
    for (int i = 0; i < N; ++i) {
      pos[p[i]] = i;
    }
    for (int i = 0, k = 0; i < N - 1; ++i, k = std::max(0, k - 1)) {
      if (pos[i] == N - 1) {
        k = 0;
        continue;
      }
      int j = p[pos[i] + 1];
      while (std::max(i, j) + k < N && S[i + k] == S[j + k]) ++k;
      lcp[pos[i]] = k;
    }
  }
  template <typename RMQ>
  int lcp_query(int i, int j, const RMQ& rmq) const {
    if (i == j) return N - i - 1;
    if (pos[i] > pos[j]) {
      std::swap(i, j);
    }
    return rmq.query(pos[i], pos[j]);  // range query should be [l, r)
  }
};
