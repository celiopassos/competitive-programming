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

using T = double;

const T EPS = 1e-9;
const T PI = acos(-1);

inline bool equal(const T& a, const T& b) { return abs(a - b) < EPS; }

struct point
{
    T x, y;
    point() : x(0), y(0) {}
    point(T x, T y) : x(x), y(y) {}
    point& operator+=(const point &rhs) { x += rhs.x, y += rhs.y; return *this; }
    point& operator-=(const point &rhs) { x -= rhs.x, y -= rhs.y; return *this; }
    point& operator*=(const T& rhs) { x *= rhs, y *= rhs; return *this; }
    point& operator/=(const T& rhs) { x /= rhs, y /= rhs; return *this; }
    point operator+(const point &rhs) const { return point(*this) += rhs; }
    point operator-(const point &rhs) const { return point(*this) -= rhs; }
    point operator*(const T& rhs) const { return point(*this) *= rhs; }
    point operator/(const T& rhs) const { return point(*this) /= rhs; }
    bool operator==(const point& rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
    bool operator<(const point& rhs) const { return pair(x, y) < pair(rhs.x, rhs.y); }
};

point operator*(const T& a, const point& p) { return p * a; }

T dot(const point& p, const point& q) { return p.x * q.x + p.y * q.y; }

T sqnorm(const point& p) { return dot(p, p); }

T norm(const point& p) { return sqrt(dot(p, p)); }

T proj(const point& p, const point& q) { return dot(p, q) / norm(q); }

T angle(const point& p, const point& q) { return acos(dot(p / norm(p), q / norm(q))); }

T det(const point& p, const point& q) { return p.x * q.y - p.y * q.x; }

bool parallel(const point& p, const point& q)
{
    return equal(det(p, q), 0);
}

point intersection(const point& p, const point& dp, const point& q, const point& dq)
{
    return p + det(q - p, dq) / det(dp, dq) * dp;
}

point rotate(const point& p, T theta) // counter-clockwise
{
    return point(cos(theta) * p.x - sin(theta) * p.y, sin(theta) * p.x + cos(theta) * p.y);
}

point rotate(const point& p) { return point(-p.y, p.x); } // pi/2 rad counter-clockwise

bool cw(const point& p, const point& q, const point& r)
{
    return det(q - p, r - q) < 0;
}

bool ccw(const point& p, const point& q, const point& r)
{
    return det(q - p, r - q) > 0;
}

vector<point> convex_hull(vector<point> a) // counter-clockwise
{
    sort(all(a)); a.erase(unique(all(a)), a.end());
    point p = a[0], q = a.back();
    vector<point> up = { p }, down = { p };
    for (int i = 1; i < sz(a); ++i)
    {
        if (i == sz(a) - 1 || cw(p, a[i], q))
        {
            while (up.size() > 1 && !cw(up[sz(up) - 2], up[sz(up) - 1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == sz(a) - 1 || ccw(p, a[i], q))
        {
            while (sz(down) >= 2 && !ccw(down[sz(down) - 2], down[sz(down) - 1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }
    up.pop_back();
    while (sz(up) > 1) down.push_back(up.back()), up.pop_back();
    return down;
}

struct line
{
    T a, b, c;
    line() : a(0), b(0), c(0) {}
    line(const T& a, const T& b, const T& c) : a(a), b(b), c(c) {}
    line(const point& p, const point& q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = - a * p.x - b * p.y;
    }
};

bool parallel(const line& U, const line& V)
{
    return equal(det({ U.a, U.b }, { V.a, V.b }), 0);
}

point intersection(const line& U, const line& V)
{
    T x = -det({ U.c, U.b }, { V.c, V.b });
    T y = -det({ U.a, U.c }, { V.a, V.c });
    T z = det({ U.a, U.b }, { V.a, V.b });
    return point(x / z, y / z);
}

bool equivalent(const line& U, const line& V)
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

