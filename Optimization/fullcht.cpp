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

template<typename T>
struct Line
{
    mutable T a, b, x;
    bool operator<(const Line& L) const { return a > L.a; }
    bool operator<(const T& t) const { return x < t; }
};

template<typename T>
struct LineContainer : multiset<Line<T>, less<>>
{
    const T lim = T(LINF);
    using iterator = typename LineContainer::iterator;

    inline T div(T a, T b)
    {
        return (a * b < 0 && a % b) ? (a / b - 1) : (a / b);
    }
    bool isect(const iterator L, const iterator R)
    {
        if (R == this->end())
        {
            L->x = lim;
            return false;
        }
        else if (L->a == R->a)
            L->x = (L->b <= R->b) ? lim : -lim;
        else
            L->x = div(R->b - L->b, L->a - R->a);
        return L->x >= R->x;
    }
    void update(T a, T b)
    {
        auto z = this->insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z))
            z = this->erase(z);

        if (x != this->begin() && isect(--x, y))
            isect(x, y = this->erase(y));

        while ((y = x) != this->begin() && (--x)->x >= y->x)
            isect(x, this->erase(y));
    }
    T get(T x) // returns minimum
    {
        if (this->empty())
            return lim;

        auto f = this->lower_bound(x);
        return (f->a) * x + (f->b);
    }
};


int main()
{ _
    exit(0);
}

