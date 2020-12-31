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

// area of largest rectangle, given heights and widths
//
// assumes last height and width are 0
// so make sure to push_back(0) !!!

template<typename T>
T largest_rectangle(const vector<T>& h, const vector<T>& w)
{
    const int n = size(h);

    stack<pair<int, T>> stk; stk.emplace(-1, 0);

    T res = 0, prefix_sum = 0;

    for (int i = 0; i < n; ++i)
    {
        while (size(stk) > 1 && h[i] <= h[stk.top().first])
        {
            int j = stk.top().first; stk.pop();
            res = max(res, h[j] * (prefix_sum - stk.top().second));
        }
        stk.emplace(i, prefix_sum += w[i]);
    }

    return res;
}

int main()
{ _
    exit(0);
}
