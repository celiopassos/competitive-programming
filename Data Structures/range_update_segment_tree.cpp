template<typename T, bool commutative = false>
struct RangeUpdate {
    int N, h;
    vector<T> st;
    RangeUpdate(int N) : N(N), h(__lg(N) + 1), st(2 * N) {}
    template<typename Iterator>
    RangeUpdate(Iterator first, Iterator last) : RangeUpdate(int(last - first)) {
        copy(first, last, begin(st) + N);
    }
    T query(int p) const {
        T res = T();
        for (p += N; p; p >>= 1) {
            res = st[p] + res;
        }
        return res;
    }
    void push(int p) {
        for (int s = h; s > 0; --s) {
            int q = p >> s;
            for (auto x : {q << 1, q << 1 | 1}) {
                st[x] = st[q] + st[x];
            }
            st[q] = T();
        }
    }
    void update(int l, int r, T value) {
        if (not commutative) {
            push(l + N);
            push(r + N - 1);
        }
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                st[l] = value + st[l];
                ++l;
            }
            if (r & 1) {
                --r;
                st[r] = value + st[r];
            }
        }
    }
};
