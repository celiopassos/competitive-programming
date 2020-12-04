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

template<typename T>
ll merge_sort(vector<T>& v, vector<T>& aux, int l, int r)
{
    if (r <= l) return 0LL;
    int m = l + (r - l) / 2;
    ll res = merge_sort(v, aux, l, m) + merge_sort(v, aux, m + 1, r);
    int x = l, y = m + 1, z = l;
    while (x <= m && y <= r)
    {
        if (v[x] <= v[y])
            aux[z++] = v[x++];
        else
            aux[z++] = v[y++], res += m - x + 1;
    }
    while (x <= m) aux[z++] = v[x++];
    while (y <= r) aux[z++] = v[y++];
    while (l <= r) v[--z] = aux[r--];
    return res;
}

template<typename T>
ll inversions(vector<T> v)
{
    static vector<T> aux;
    aux.resize(max(size(aux), size(v)));
    return merge_sort(v, aux, 0, size(v) - 1);
}

int main()
{ _
    exit(0);
}
