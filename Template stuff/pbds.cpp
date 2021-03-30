#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace __gnu_pbds; // policy-based

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int FIXED_RANDOM = (int)chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(FIXED_RANDOM);

struct custom_hash {
    int operator()(int x) const {
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};

template<typename T>
using hash_table = gp_hash_table<int, T, custom_hash>;
