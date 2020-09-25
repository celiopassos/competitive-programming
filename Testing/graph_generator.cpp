#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) (X).begin(), (X).end()
#define sz(X) (int)X.size()

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;

int main()
{ _
AGAIN:
    const int n = 10;

    int A[n][n];
    memset(A, 0, sizeof(A));

    uniform_int_distribution unif(0, n - 1);

    int m = (1 + unif(rng)) * (1 + unif(rng)) / 3;

    int MAX = 1e6;
    for (int ct = 0; ct < m;)
    {
        if (--MAX == 0) goto AGAIN;
        int u = unif(rng), v = unif(rng);
        if (u != v && not (A[u][v]++ || A[v][u]++)) ++ct;

    }

    int shift = unif(rng);

    cout << n << " " << m << endl;;
    for (int u = 0; u < n; ++u)
        for (int v = u + 1; v < n; ++v)
            if (A[u][v]) cout << (u + shift) % n + 1 << " " << (v + shift) % n + 1 << endl;

    exit(0);
}

