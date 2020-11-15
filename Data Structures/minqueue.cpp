#include "bits/stdc++.h"

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(x) cerr << #x << " == " << (x) << '\n';
#define all(X) begin(X), end(X)
#define size(X) (int)std::size(X)

using ll = long long;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;

template<typename T>
struct M1
{
    static constexpr T id = INF;
    static T op(const T& x, const T& y) { return min(x, y); }
};

template<typename M, bool top_down = false>
class MinimumStack
{
private:
    using T = typename remove_const<decltype(M::id)>::type;
    stack<pair<T, T>> st;
public:
    T top() const { return st.top().first; }
    T minimum() const { return st.empty() ? M::id : st.top().second; }
    void push(T value)
    {
        if (top_down)
            st.push(pair<T, T>(value, op(value, minimum())));
        else
            st.push(pair<T, T>(value, op(minimum(), value)));
    }
    void pop() { st.pop(); }
    bool empty() const { return st.empty(); }
    int (size)() const { return size(st); }
};

template<typename M>
class MinimumQueue
{
private:
    using T = typename remove_const<decltype(M::id)>::type;
    MinimumStack<M, false> in;
    MinimumStack<M, true> out;
    void move()
    {
        if (out.empty()) while (not in.empty())
        {
            out.push(in.top());
            in.pop();
        }
    }
public:
    T front() { move(); return out.top(); }
    T minimum() const { return op(out.minimum(), in.minimum()); }
    void push(T value) { in.push(value); }
    void pop() { move(); out.pop(); }
    bool empty() const { return in.empty() && out.empty(); }
    int (size)() const { return size(in) + size(out); }
};

int main()
{ _
    exit(0);
}

