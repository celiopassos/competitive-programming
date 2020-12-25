#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")

#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/rope>

using namespace std;
using namespace __gnu_pbds; // policy-based
using namespace __gnu_cxx; // rope

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();

mt19937 rng(FIXED_RANDOM);

struct custom_hash
{
    int operator()(int x) const
    {
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};

template<typename T>
using hash_table = gp_hash_table<int, T, custom_hash>;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

int main()
{ _
    exit(0);
}
