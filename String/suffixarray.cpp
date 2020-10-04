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

vector<int> sort_cyclic_shifts(const string& s)
{
    int n = sz(s);
    const int alphabet = 256;
    vector p(n, 0), c(n, 0), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++) cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++)
    {
        if (s[p[i]] != s[p[i-1]]) classes++;
        c[p[i]] = classes - 1;
    }
    vector pn(n, 0), cn(n, 0);
    for (int h = 0; (1 << h) < n; ++h)
    {
        for (int i = 0; i < n; i++)
        {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++) cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++)
        {
            pair cur = { c[p[i]], c[(p[i] + (1 << h)) % n] };
            pair prev = { c[p[i-1]], c[(p[i-1] + (1 << h)) % n] };
            if (cur != prev) ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array(string s)
{
    s += "$";
    auto sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

vector<int> lcp_array(const string& s, const vector<int>& p)
{
    int n = sz(s);
    vector pos(n, 0);
    for (int i = 0; i < n; ++i) pos[p[i]] = i;

    int k = 0;
    vector lcp(n - 1, 0);
    for (int i = 0; i < n; ++i)
    {
        if (pos[i] == n - 1) { k = 0; continue; }
        int j = p[pos[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[pos[i]] = k;
        if (k) --k;
    }
    return lcp;
}

int main()
{ _
    // auto lcp_query = [&](int i, int j)
    // {
    //     if (i == j) return n - i;
    //     if (pos[i] > pos[j]) swap(i, j);
    //     return sparse_table.query(pos[i], pos[j] - 1);
    // };

    exit(0);
}

