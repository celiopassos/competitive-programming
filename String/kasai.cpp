template<typename Iterator>
std::vector<int> kasai(Iterator first, const std::vector<int>& p) {
    int N = p.size();
    std::vector<int> lcp(N), pos(N);
    for (int i = 0; i < N; ++i) {
        pos[p[i]] = i;
    }
    for (int i = 0, k = 0; i < N - 1; ++i, k = std::max(0, k - 1)) {
        if (pos[i] == N - 1) {
            k = 0;
            continue;
        }
        for (int j = p[pos[i] + 1]; std::max(i, j) + k < N && first[i + k] == first[j + k]; ++k);
        lcp[pos[i]] = k;
    }
    return lcp;
}
