#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

int main()
{ _
    int n; cin >> n;
    vi a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    const int N = 20;

    vi F(1 << N, 0);
    for (int i = 0; i < n; ++i)
        F[i] = a[i];

    // for each x, computes sum of a[i] for i subset of x
    for (int i = 0; i < N; ++i)
        for (int x = 0; x < (1 << N); ++x)
            if (x & (1 << i))
                F[x] += F[x ^ (1 << i)];

    exit(0);
}

