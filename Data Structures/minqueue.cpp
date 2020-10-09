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

template<typename T, bool top_down = false>
class MinimumStack
{
private:
    const T Tid;
    const function<T(T, T)> op;
    stack<pair<T, T>> st;
public:
    MinimumStack(const T Tid, const function<T(T, T)> op) : Tid(Tid), op(op) { }
    T top() const { return st.top().first; }
    T minimum() const { return st.empty() ? Tid : st.top().second; }
    void push(T value)
    {
        if (top_down)
            st.push(pair<T, T>(value, op(value, minimum())));
        else
            st.push(pair<T, T>(value, op(minimum(), value)));
    }
    void pop() { st.pop(); }
    bool empty() const { return st.empty(); }
    int size() const { return size(st); }
};

template<typename T>
class MinimumQueue
{
private:
    const function<T(T, T)> op;
    MinimumStack<T, false> in;
    MinimumStack<T, true> out;
    void move()
    {
        if (out.empty()) while (not in.empty())
        {
            out.push(in.top());
            in.pop();
        }
    }
public:
    MinimumQueue(const T Tid, const function<T(T, T)> op) : op(op), in(Tid, op), out(Tid, op) { }
    T front() const { move(); return out.top(); }
    T minimum() const { return op(out.minimum(), in.minimum()); }
    void push(T value) { in.push(value); }
    void pop() { move(); out.pop(); }
    bool empty() const { return in.empty() && out.empty(); }
    int size() const { return size(in) + size(out); }
};

int main()
{ _
    exit(0);
}

