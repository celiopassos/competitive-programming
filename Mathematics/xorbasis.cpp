#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<int N> struct XORBasis
{
private:
    using V = bitset<N>;
    array<V, N> basis, alpha;
    int dim = 0;
    auto reduce(V& x) const
    {
        V coef;
        for (int i = N - 1; i >= 0 && x.any(); --i)
        {
            if (x[i] == 0) continue;
            if (basis[i] == 0) return pair(i, coef);
            x ^= basis[i], coef ^= alpha[i];
        }
        return pair(-1, coef);
    }
public:
    bool insert(V x)
    {
        auto [i, coef] = reduce(x);
        if (i == -1) return false;
        basis[i] = x, dim += 1;
        alpha[i] = coef;
        alpha[i][dim - 1] = 1;
        return true;
    }
    auto solve(V x) const
    {
        auto [i, coef] = reduce(x);
        return pair(i == -1, coef);
    }
    V combination(V coef) const
    {
        V res;
        for (int i = 0; i < N; ++i)
            if (coef[i]) res ^= basis[i];
        return res;
    }
};

int main()
{ _
    exit(0);
}

