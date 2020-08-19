#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// xz

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

