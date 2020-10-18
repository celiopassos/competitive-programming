#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename...>
struct Pointwise
{
    Pointwise() { }
    Pointwise(auto init) { (void)init; }
    Pointwise& operator+=(const Pointwise& rhs) { (void)rhs; return *this; };
    Pointwise& operator-=(const Pointwise& rhs) { (void)rhs; return *this; };
    Pointwise& operator*=(const Pointwise& rhs) { (void)rhs; return *this; };
    Pointwise& operator/=(const Pointwise& rhs) { (void)rhs; return *this; };
    Pointwise operator+(const Pointwise& rhs) const { (void)rhs; return Pointwise(); };
    Pointwise operator-(const Pointwise& rhs) const { (void)rhs; return Pointwise(); };
    Pointwise operator*(const Pointwise& rhs) const { (void)rhs; return Pointwise(); };
    Pointwise operator/(const Pointwise& rhs) const { (void)rhs; return Pointwise(); };
    tuple<> get() { return tuple<>(); }
};

template<typename T, typename... Ts>
struct Pointwise<T, Ts...>
{
    T value;
    Pointwise<Ts...> nxt;
    Pointwise(T value, Ts... args) : value(value), nxt(args...) { }
    Pointwise(auto init) : value(init), nxt(init) { }
    Pointwise() : value(T()), nxt() { }
    Pointwise& operator+=(const Pointwise& rhs) { value += rhs.value, nxt += rhs.nxt; return *this; };
    Pointwise& operator-=(const Pointwise& rhs) { value -= rhs.value, nxt -= rhs.nxt; return *this; };
    Pointwise& operator*=(const Pointwise& rhs) { value *= rhs.value, nxt *= rhs.nxt; return *this; };
    Pointwise& operator/=(const Pointwise& rhs) { value /= rhs.value, nxt /= rhs.nxt; return *this; };
    Pointwise operator+(const Pointwise& rhs) const { return Pointwise(*this) += rhs; };
    Pointwise operator-(const Pointwise& rhs) const { return Pointwise(*this) -= rhs; };
    Pointwise operator*(const Pointwise& rhs) const { return Pointwise(*this) *= rhs; };
    Pointwise operator/(const Pointwise& rhs) const { return Pointwise(*this) /= rhs; };
    auto get() { return tuple_cat(tuple<T&>(value), nxt.get()); }
};

int main()
{ _
    exit(0);
}

