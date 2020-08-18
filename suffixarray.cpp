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

typedef complex<int> cp;

vector<vi> c;
vi sort_cyclic_shifts(const string& s)
{
    int n = sz(s);
    const int alphabet = 256;
    vi p(n), cnt(max(alphabet, n), 0);
    c.push_back(vi(n));
    for (int i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (int i = 1; i < alphabet; ++i)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i)
        p[--cnt[s[i]]] = i;
    c[0][p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i)
    {
        if (s[p[i]] != s[p[i - 1]])
            ++classes;
        c[0][p[i]] = classes - 1;
    }
    vi pn(n);
    for (int h = 0; (1 << h) < n; ++h)
    {
        c.push_back(vi(n));
        for (int i = 0; i < n; ++i)
        {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; ++i)
            ++cnt[c[h][pn[i]]];
        for (int i = 1; i < classes; ++i)
            cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i)
            p[--cnt[c[h][pn[i]]]] = pn[i];
        c[h + 1][p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; ++i)
        {
            cp cur = { c[h][p[i]], c[h][(p[i] + (1 << h)) % n] };
            cp prev = { c[h][p[i - 1]], c[h][(p[i - 1] + (1 << h)) % n] };
            if (cur != prev)
                ++classes;
            c[h + 1][p[i]] = classes - 1;
        }
    }
    return p;
}

vi suffix_array(string s)
{
    s += "$";
    vi sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

int lcp(int i, int j)
{
    int ans = 0, n = sz(c[0]);
    for (int k = sz(c) - 1; k >= 0; k--)
    {
        if (max(i, j) < n && c[k][i] == c[k][j])
        {
            ans += 1 << k;
            i += 1 << k;
            j += 1 << k;
        }
    }
    return ans;
}

int main()
{ _
    exit(0);
}

