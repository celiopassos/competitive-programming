template<typename Iterator>
std::vector<int> sort_cyclic_shifts(Iterator first, Iterator last) {
    int N = last - first;
    std::vector<int> p(N), inv(N), tmp(N), cnt(N);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j){ return first[i] < first[j]; });
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
