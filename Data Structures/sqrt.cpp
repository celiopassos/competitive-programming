// To do:
//
// * Range query
// * Order of key on ranges
// * Compatibility with lazy context

template<typename T, int K = 400>
struct SQRT
{
    const int n, blocks;
 
    vector<T> arr, offset;
    vector<vector<int>> bucket;
 
    void sort_bucket(int b) {
        sort(all(bucket[b]), [&](int i, int j){ return arr[i] < arr[j]; });
    }
 
    SQRT(const vector<T>& arr) : n(size(arr)), blocks((n + K - 1) / K), arr(arr), offset(blocks, 0), bucket(blocks) {
        for (int b = 0; b < blocks; ++b) {
            int len = min(K, n - b * K);
            bucket[b].resize(len), iota(all(bucket[b]), b * K);
            sort_bucket(b);
        }
    }
    T query(int p) { return arr[p] + offset[p / K]; }
    // O((n/K) + Klog(K))
    void update(int l, int r, T add) {
        int s = l / K, e = r / K;
 
        for (int b = s + 1; b <= e - 1; ++b)
            offset[b] += add;
        for (int i = l; i <= min(r, s * K + K - 1); ++i)
            arr[i] += add;
        if (s != e) for (int i = e * K; i <= r; ++i)
            arr[i] += add;
 
        sort_bucket(s), sort_bucket(e);
    }
    // O((n/K)log(K))
    int order_of_key(T key) {
        int res = 0;
        for (int b = 0; b < blocks; ++b) {
            auto iter = lower_bound(all(bucket[b]), key - offset[b], [&](int i, T x){ return arr[i] < x; });
            res += (int)distance(begin(bucket[b]), iter);
        }
        return res;
    }
};
