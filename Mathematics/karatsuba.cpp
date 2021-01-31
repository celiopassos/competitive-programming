template<typename T, int K>
void karatsuba(int n, T* a, T* b, T* res, T* tmp)
{
    if (n <= K)
    {
        for (int i = 0; i < n; ++i)
           for (int j = 0; j < n; ++j)
              res[i + j] += a[i] * b[j];
    }
    else
    {
        int mid = n / 2, N = 2 * n;

        T *r0 = tmp, *r1 = tmp + n;
        karatsuba<T, K>(mid, a, b, r0, tmp + N);
        karatsuba<T, K>(mid, a + mid, b + mid, r1, tmp + N);
 
        for (int i = 0; i < n - 1; ++i)
        {
            res[i] += r0[i];
            res[mid + i] -= (r0[i] + r1[i]);
            res[n + i] += r1[i];
        }

        for (int i = 0; i < mid; ++i)
        {
            r0[i] = a[i] + a[mid + i];
            r1[i] = b[i] + b[mid + i];
        }
        karatsuba<T, K>(mid, r0, r1, res + mid, tmp + N);

        fill(tmp, tmp + N, T(0));
    }
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

    vector<T> res(2 * N - 1, T(0)), tmp(4 * N, T(0));

    karatsuba<T, K>(N, a.data(), b.data(), res.data(), tmp.data());

    res.resize(n + m - 1);

    return res;
}
