// 998244353 = 1 + 7 * 17 * (2 ^ 23)
// 469762049 = 1 + 7 * (2 ^ 26)
// 167772161 = 1 + 5 * (2 ^ 25)

constexpr int MODs[] = { 998244353, 469762049, 167772161 };
constexpr int preexp[] = { 7 * 17, 7, 5 };
constexpr int explog[] = { 23, 26, 25 };
constexpr int primitive[] = { 3, 3, 3 };

using M998 = Mint<MODs[0]>;
template<>
M998 getroot<M998>(int N) {
     return M998(primitive[0]).power(preexp[0] * (1LL << explog[0]) / N);
}
