template <typename Iterator>
std::vector<int> prefix_function(Iterator first, Iterator last) {
  int N = last - first;
  std::vector<int> p(N + 1, 0);
  for (int len = 2; len <= N; ++len) {
    int x = p[len - 1];
    while (x && first[len - 1] != first[x]) x = p[x];
    if (first[len - 1] == first[x]) ++x;
    p[len] = x;
  }
  return p;
}
