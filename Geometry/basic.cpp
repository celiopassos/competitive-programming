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

const double PI = acos(-1);
const double EPS = 1e-9;

template<typename T>
bool equal(T a, T b)
{
    return abs(a - b) <= EPS;
}

template<typename T>
struct pt
{
    T x, y;
    pt() : x(0), y(0) {}
    pt(T x, T y) : x(x), y(y) {}
    pt& operator+=(pt rhs) { x += rhs.x, y += rhs.y; return *this; }
    pt& operator-=(pt rhs) { x -= rhs.x, y -= rhs.y; return *this; }
    pt& operator*=(T rhs) { x *= rhs, y *= rhs; return *this; }
    pt& operator/=(T rhs) { x /= rhs, y /= rhs; return *this; }
    pt operator+(pt rhs) const { return pt(*this) += rhs; }
    pt operator-(pt rhs) const { return pt(*this) -= rhs; }
    pt operator*(T rhs) const { return pt(*this) *= rhs; }
    pt operator/(T rhs) const { return pt(*this) /= rhs; }
    bool operator==(pt rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
    bool operator<(pt rhs) const { return pair(x, y) < pair(rhs.x, rhs.y); }
};

template<typename T>
pt<T> operator*(const T& a, pt<T> p) { return p * a; }

template<typename T>
T dot(pt<T> p, pt<T> q) { return p.x * q.x + p.y * q.y; }

template<typename T>
T sqnorm(pt<T> p) { return dot(p, p); }

template<typename T>
T norm(pt<T> p) { return sqrt(dot(p, p)); }

template<typename T>
T proj(pt<T> p, pt<T> q) { return dot(p, q) / norm(q); }

template<typename T>
T angle(pt<T> p, pt<T> q) { return acos(dot(p / norm(p), q / norm(q))); }

template<typename T>
T det(pt<T> p, pt<T> q) { return p.x * q.y - p.y * q.x; }

template<typename T>
bool parallel(pt<T> p, pt<T> q)
{
    return equal(det(p, q), 0);
}

template<typename T>
pt<T> intersection(pt<T> p, pt<T> dp, pt<T> q, pt<T> dq)
{
    return p + det(q - p, dq) / det(dp, dq) * dp;
}

template<typename T>
pt<T> rotate(pt<T> p, T theta) // counter-clockwise
{
    return pt<T>(cos(theta) * p.x - sin(theta) * p.y, sin(theta) * p.x + cos(theta) * p.y);
}

template<typename T>
pt<T> rotate(pt<T> p) { return pt<T>(-p.y, p.x); } // pi/2 rad counter-clockwise

template<typename T>
bool cw(pt<T> p, pt<T> q, pt<T> r)
{
    return det(q - p, r - q) < 0;
}

template<typename T>
bool ccw(pt<T> p, pt<T> q, pt<T> r)
{
    return det(q - p, r - q) > 0;
}

template<typename T>
vector<pt<T>> convex_hull(vector<pt<T>> a) // counter-clockwise
{
    sort(all(a)); a.erase(unique(all(a)), a.end());
    pt<T> p = a[0], q = a.back();
    vector<pt<T>> up = { p }, down = { p };
    for (int i = 1; i < size(a); ++i)
    {
        if (i == size(a) - 1 || cw(p, a[i], q))
        {
            while (size(up) > 1 && !cw(up[size(up) - 2], up[size(up) - 1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == size(a) - 1 || ccw(p, a[i], q))
        {
            while (size(down) >= 2 && !ccw(down[size(down) - 2], down[size(down) - 1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    up.pop_back();
    while (size(up) > 1) down.push_back(up.back()), up.pop_back();
    return down;
}

template<typename T>
struct line
{
    T a, b, c;
    line() : a(0), b(0), c(0) {}
    line(const T& a, const T& b, const T& c) : a(a), b(b), c(c) {}
    line(pt<T> p, pt<T> q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = - a * p.x - b * p.y;
    }
};

template<typename T>
bool parallel(line<T> U, line<T> V)
{
    return equal(det({ U.a, U.b }, { V.a, V.b }), 0);
}

template<typename T>
pt<T> intersection(line<T> U, line<T> V)
{
    T x = -det({ U.c, U.b }, { V.c, V.b });
    T y = -det({ U.a, U.c }, { V.a, V.c });
    T z = det({ U.a, U.b }, { V.a, V.b });
    return pt<T>(x / z, y / z);
}

template<typename T>
bool equivalent(line<T> U, line<T> V)
{
    return
        equal(det({ U.a, U.b }, { V.a, V.b }), 0) &&
        equal(det({ U.a, U.c }, { V.a, V.c }), 0) &&
        equal(det({ U.b, U.c }, { V.b, V.c }), 0);
}

int main()
{ _
    exit(0);
}

