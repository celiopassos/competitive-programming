#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// with K = n / sqrt(q), complexity is O(n * sqrt(q))

void mo(auto Q, auto& eval, auto& remove, auto& insert, int K)
{
    int q = size(Q);
    vector<int> Z(q, 0); iota(all(Z), 0);

    auto cmp = [&](int i, int j)
    {
        if (Q[i].first / K != Q[j].first / K)
            return Q[i].first / K < Q[j].first / K;
        if ((Q[i].first / K) & 1)
            return Q[i].second > Q[j].second;
        return Q[i].second < Q[j].second;
    };
    sort(all(Z), cmp);

    int lcur = 0, rcur = 0; insert(0);

    auto update = [&](int l, int r)
    {
        while (l < lcur) insert(--lcur);
        while (rcur < r) insert(++rcur);
        while (lcur < l) remove(lcur++);
        while (r < rcur) remove(rcur--);
    };

    for (auto z : Z)
    {
        update(Q[z].first, Q[z].second);
        eval(z);
    }
}

int main()
{ _
    exit(0);
}
