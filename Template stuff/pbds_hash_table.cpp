struct custom_hash {
    int operator()(int x) const {
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};
template<typename T>
using hash_table = gp_hash_table<int, T, custom_hash>;
