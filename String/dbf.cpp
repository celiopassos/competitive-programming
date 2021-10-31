struct dbf_t {
    int N;
    std::vector<int> log;
    std::vector<std::vector<int>> p, rank;
    template<typename Iterator>
    dbf_t(Iterator first, Iterator last) : N(last - first), log(N + 1) {
        for (int n = 2; n <= N; ++n) {
            log[n] = 1 + log[n >> 1];
        }
        p.assign(log[N] + 1, std::vector<int>(N));
        rank.assign(log[N] + 1, std::vector<int>(N));
        std::iota(p[0].begin(), p[0].end(), 0);
        std::sort(p[0].begin(), p[0].end(), [&](int i, int j) { return first[i] < first[j]; });
        for (int i = 1; i < N; ++i) {
            rank[0][p[0][i]] = rank[0][p[0][i - 1]] + (first[p[0][i]] != first[p[0][i - 1]]);
        }
        std::vector<int> cnt(N), tmp(N);
        for (int k = 0; k < log[N]; ++k) {
            for (int i = 0; i < N; ++i) {
                tmp[N - 1 - i] = (p[k][i] + N - (1 << k)) % N;
                ++cnt[rank[k][p[k][i]]];
            }
            std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
            for (auto i : tmp) {
                p[k + 1][--cnt[rank[k][i]]] = i;
            }
            std::fill(cnt.begin(), cnt.end(), 0);
            auto key = [&](int i) {
                return std::pair(rank[k][i], rank[k][(i + (1 << k)) % N]);
            };
            for (int i = 1; i < N; ++i) {
                rank[k + 1][p[k + 1][i]] = rank[k + 1][p[k + 1][i - 1]] + (key(p[k + 1][i]) != key(p[k + 1][i - 1]));
            }
        }
    }
    std::pair<int, int> key(int i, int len) const {
        int k = log[len];
        return std::pair(rank[k][i], rank[k][(i + len - (1 << k)) % N]);
    };
    bool cmp(std::array<int, 2> S, std::array<int, 2> T) const {
        int lenS = S[1] - S[0], lenT = T[1] - T[0], min = std::min(lenS, lenT);
        auto keyS = key(S[0], min), keyT = key(T[0], min);
        return keyS != keyT ? keyS < keyT : lenS < lenT;
    }
};
