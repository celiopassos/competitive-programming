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

template<int N>
struct Sieve
{
private:
    array<int, N + 1> lp, pr;
    int *b, *e;
public:
    constexpr Sieve() : lp{ 0 }, pr{ 0 }, b(&pr[0]), e(&pr[0])
    {
        for (int i = 2; i <= N; ++i)
        {
            if (lp[i] == 0) lp[i] = *(e++) = i;
            for (auto p : pr)
            {
                if (p > lp[i] || i * p > N || p == 0) break;
                lp[i * p] = p;
            }
        }
    }
    constexpr int operator[](int i) const { return lp[i]; }
    constexpr int* begin() const { return b; }
    constexpr int* end() const { return e; }
};

int main()
{ _
    exit(0);
}

