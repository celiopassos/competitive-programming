std::pair<std::vector<int>, std::vector<int>> sieve(int N) {
  std::vector<int> lp(N + 1), pr;
  for (int i = 2; i <= N; ++i) {
    if (lp[i] == 0) {
      pr.push_back(lp[i] = i);
    }
    for (auto p : pr) {
      if (p > lp[i] || i * p > N) break;
      lp[i * p] = p;
    }
  }
  return {lp, pr};
}
