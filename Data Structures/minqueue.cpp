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

// xz

template<typename T, bool bottom_up>
class MinimumStack
{
private:
    const T Tid;
    const function<T(const T&, const T&)>& op;
    stack<pair<T, T>> st;
public:
    MinimumStack(const T Tid, const function<T(const T&, const T&)>& op) : Tid(Tid), op(op) { }
    T top() const { return st.top().first; }
    T minimum() const { return st.empty() ? Tid : st.top().second; }
    void push(const T& value)
    {
        if (bottom_up)
            st.push(pair<T, T>(value, op(minimum(), value)));
        else
            st.push(pair<T, T>(value, op(value, minimum())));
    }
    void pop() { st.pop(); }
    bool empty() const { return st.empty(); }
};

template<typename T>
class MinimumQueue
{
private:
    const function<T(const T&, const T&)>& op;
    MinimumStack<T, true> in;
    MinimumStack<T, false> out;
    void move()
    {
        if (out.empty()) while (not in.empty())
        {
            out.push(in.top());
            in.pop();
        }
    }
public:
    MinimumQueue(const T Tid, const function<T(const T&, const T&)>& op) : op(op), in(Tid, op), out(Tid, op) { }
    T front() const { move(); return out.top(); }
    T minimum() const { return op(out.minimum(), in.minimum()); }
    void push(const T& value) { in.push(value); }
    void pop() { move(); out.pop(); }
    bool empty() const { return in.empty() && out.empty(); }
};

int main()
{ _
    MinimumQueue<string> q("", [](const string& a, const string& b){ return a + b; });
    for (string s; cin >> s;)
    {
        q.push(s);
        cout << q.minimum() << endl;
    }
    exit(0);
}

