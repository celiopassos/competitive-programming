template<typename Iterator>
vector<int> kasai(Iterator first, const vector<int>& p) {
    int N = (int)p.size();
    vector<int> lcp(N), pos(N);
    for (int i = 0; i < N; ++i) {
        pos[p[i]] = i;
    }
    for (int i = 0, k = 0; i < N - 1; ++i, k = max(0, k - 1)) {
        if (pos[i] == N - 1) {
            k = 0;
            continue;
        }
        for (int j = p[pos[i] + 1]; max(i, j) + k < N && first[i + k] == first[j + k]; ++k);
        lcp[pos[i]] = k;
    }
    return lcp;
}
