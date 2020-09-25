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

template<typename T, typename F>
struct LiChaoTree
{
    const int L, R;
    const function<T(F, int)> get;
    const F id;
    vector<F> st;
    vector<int> LEFT, RIGHT;
    LiChaoTree(int L, int R, function<T(F, int)> get, F id) :
        L(L), R(R), get(get), id(id) { create(); }
    int create()
    {
        LEFT.push_back(-1);
        RIGHT.push_back(-1);
        st.push_back(id);
        return sz(st) - 1;
    }
    int get_left(int p) { return LEFT[p] == -1 ? LEFT[p] = create() : LEFT[p]; }
    int get_right(int p) { return RIGHT[p] == -1 ? RIGHT[p] = create() : RIGHT[p]; }
    void update(F nw)
    {
        for (int p = 0, l = L, r = R; l <= r;)
        {
            int m = l + (r - l) / 2;
            bool left = get(nw, l) < get(st[p], l);
            bool mid = get(nw, m) < get(st[p], m);

            if (mid) swap(nw, st[p]);
            if (left != mid) p = get_left(p), r = m;
            else p = get_right(p), l = m + 1;
        }
    }
    T compute(int x)
    {
        T res = T(LINF);
        for (int p = 0, l = L, r = R; l <= r;)
        {
            res = min(res, get(st[p], x));
            int m = l + (r - l) / 2;
            if (x == m) break;
            else if (x < m) r = m, p = get_left(p);
            else l = m + 1, p = get_right(p);
        }
        return res;
    }
};

int main()
{ _
    exit(0);
}

