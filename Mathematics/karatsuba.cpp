template<typename T, int K>
vector<T> karatsuba(int n, const vector<T>& a, const vector<T>& b)
{
    vector<T> res(2 * n - 1, T(0));
    if (n <= K)
    {
        for (int i = 0; i < n; ++i)
           for (int j = 0; j < n; ++j)
              res[i + j] += a[i] * b[j];
    }
    else
    {
        int mid = n >> 1;
        vector<T> alow(begin(a), begin(a) + mid), ahigh(mid + all(a));
        vector<T> blow(begin(b), begin(b) + mid), bhigh(mid + all(b));

        auto r0 = karatsuba<T, K>(mid, alow, blow), r1 = karatsuba<T, K>(mid, ahigh, bhigh);

        for (int i = 0; i < mid; ++i) alow[i] += ahigh[i], blow[i] += bhigh[i];

        auto E = karatsuba<T, K>(mid, alow, blow);

        for (int i = 0; i < n - 1; ++i)
        {
            res[i] += r0[i];
            res[mid + i] += E[i] - (r0[i] + r1[i]);
            res[n + i] += r1[i];
        }
    }
    return res;
}

int logceil(int n)
{
    return __builtin_clz(1) - __builtin_clz(n) + !!(n & (n - 1));
}

template<typename T, int K = 64>
vector<T> karatsuba(vector<T> a, vector<T> b)
{
    const int n = size(a), m = size(b), N = 1 << logceil(max(n, m));
    a.resize(N, T(0)), b.resize(N, T(0));
    auto res = karatsuba<T, K>(N, a, b);
    res.resize(n + m - 1);
    return res;
}
