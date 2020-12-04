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

string max_suffix(string s)
{
    s += "#";
    string res; res.push_back(s[0]);
    for (int i = 1; i < size(s); ++i)
    {
        int k = 0;
        while (k < size(res) && s[i + k] == res[k]) ++k;
        if (s[i + k] > res[0])
            res = s.substr(i + k, 1);
        else if (k == size(res) || s[i + k] < res[k])
            res += s.substr(i, k + 1);
        else
            res = s.substr(i, k + 1);
        i += k;
    }
    res.pop_back();
    return res;
}

int main()
{ _
    exit(0);
}
