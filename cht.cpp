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

typedef int ftype;
typedef complex<ftype> point;

ftype dot(point a, point b)
{
    return (conj(a) * b).real();
}

ftype cross(point a, point b)
{
    return (conj(a) * b).imag();
}

vector<point> hull, vecs;

void add_line(ftype k, ftype b)
{
    point nw = {k, b};
    while (!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0)
    {
        hull.pop_back();
        vecs.pop_back();
    }
    if (!hull.empty())
        vecs.pb(point(0, 1) * (nw - hull.back())); // CHANGE THIS IF ADDING BACKWARDS
    hull.pb(nw);
}

int get(ftype x)
{
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b){ return cross(a, b) > 0; }); // CHANGE THIS IF ADDING BACKWARDS
    return dot(query, hull[it - vecs.begin()]); // CHANGE THIS IF ADDING BACKWARDS
}

int main()
{ _
    exit(0);
}

