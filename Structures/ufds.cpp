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

class UFDS
{
private:
    vector<int> p, rk, sz;
    int num_disjoint_sets;
public:
    UFDS(int n)
    {
        rk.assign(n, 0);
        p.assign(n, 0);
        for (int i = 0; i < n; ++i)
            p[i] = i;
        num_disjoint_sets = n;
        sz.assign(n, 1);
    }
    int find_set(int i)
    {
        return (p[i] == i) ? i : (p[i] = find_set(p[i]));
    }
    bool is_same_set(int i, int j)
    {
        return find_set(i) == find_set(j);
    }
    void union_set(int i, int j)
    {
        int x = find_set(i), y = find_set(j);
        if (x != y)
        {
            --num_disjoint_sets;
            if (rk[x] >= rk[y])
            {
                p[y] = x;
                rk[x] += (rk[x] == rk[y]);
                sz[x] += sz[y];
            }
            else
            {
                p[x] = y;
                sz[y] += sz[x];
            }
        }
    }
    int set_size(int i)
    {
        return sz[find_set(i)];
    }
    int num_sets()
    {
        return num_disjoint_sets;
    }
};

int main()
{ _
    exit(0);
}

