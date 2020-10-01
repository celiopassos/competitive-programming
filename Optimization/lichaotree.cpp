#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) X.begin(), X.end()
#define sz(X) (int)X.size()

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

// May define any kind of function,
// as long as intersections are unique.
// Should default to constant = infinity

// E.g., linear function:

template<typename T>
struct Function
{
    T a = 0, b = numeric_limits<T>::max();
    T operator[](T x) const { return a * x + b; }
    bool operator==(const Function& rhs) const
    {
        return a == rhs.a && b == rhs.b;
    }
};

template<typename Func, typename Codomain, typename Domain=Codomain>
struct LiChaoTree
{
    Domain L, R;
    Func inf = Func();
    vector<Func> st;
    vector<int> LEFT, RIGHT;

    LiChaoTree(Domain L, Domain R) : L(L), R(R) { create(); }

    int size() { return sz(st); }
    int create()
    {
        LEFT.push_back(-1), RIGHT.push_back(-1);
        st.push_back(inf);
        return size() - 1;
    }
    int left(int p) { return LEFT[p] == -1 ? LEFT[p] = create() : LEFT[p]; }
    int right(int p) { return RIGHT[p] == -1 ? RIGHT[p] = create() : RIGHT[p]; }
    void update(Func add)
    {
        Domain l = L, r = R; int p = 0;
        while (l <= r)
        {
            Domain m = l + (r - l) / 2;
            bool lft = add[l] < st[p][l];
            bool mid = add[m] < st[p][m];
            bool stop = (st[p] == inf);
            if (mid) swap(add, st[p]);
            if (stop) break;
            if (lft != mid)
                p = left(p), r = m;
            else
                p = right(p), l = m + 1;
        }
    }
    Codomain compute(Domain x) // returns minimum
    {
        Codomain res = inf[x];
        Domain l = L, r = R;
        int p = 0;
        while (l <= r)
        {
            if (st[p] == inf) break;
            res = min(res, st[p][x]);
            Domain m = l + (r - l) / 2;
            if (x == m) break;
            else if (x < m)
                p = left(p), r = m;
            else
                p = right(p), l = m + 1;
        }
        return res;
    }
};

int main()
{ _
    exit(0);
}

