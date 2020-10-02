#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

int main()
{ _
    const int N = 1e7;
    int lp[N + 1] = { 0 };
    vi pr;

    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0)
            lp[i] = i, pr.push_back(i);

        for (auto p : pr)
        {
            if (p > lp[i] || i * p > N)
                break;
            lp[i * p] = p;
        }
    }

    exit(0);
}

