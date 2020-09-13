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
{ _
    int q; cin >> q;
    vector<int> l(q, 0), r(q, 0);

    int k = 1;
    while (k * k <= n) ++k;

    vector<int> I(q, 0); iota(all(I), 0);
    sort(all(I), [&](int i, int j)
        {
            if (l[i] / k != l[j] / k) return l[i] / k < l[j] / k;
            if ((l[i] / k) & 1) return r[j] < r[i];
            else return r[i] < r[j];
        }
    );

    int lcur = 0, rcur = 0;

    auto remove = [&](int x) {  };
    auto insert = [&](int x) {  };

    auto update = [&](int l, int r)
    {
        while (l < lcur) insert(a[--lcur]);
        while (rcur < r) insert(a[++rcur]);
        while (lcur < l) remove(a[lcur++]);
        while (r < rcur) remove(a[rcur--]);
    };

    vector<int> ans(q, 0);
    for (auto z : I)
    {
        update(l[z], r[z]);
    }

    for (int z = 0; z < q; ++z)
        cout << ans[z] << endl;

    exit(0);
}

