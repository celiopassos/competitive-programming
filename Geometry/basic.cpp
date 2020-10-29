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

const double PI = acos(-1);
const double EPS = 1e-9;

template<typename T>
bool equal(T a, T b)
{
    return abs(a - b) <= EPS;
}

template<typename T>
struct point
{
    T x, y;
    point() : x(0), y(0) {}
    point(T x, T y) : x(x), y(y) {}
    point& operator+=(const point& rhs) { x += rhs.x, y += rhs.y; return *this; }
    point& operator-=(const point& rhs) { x -= rhs.x, y -= rhs.y; return *this; }
    point& operator*=(const T& rhs) { x *= rhs, y *= rhs; return *this; }
    point& operator/=(const T& rhs) { x /= rhs, y /= rhs; return *this; }
    point operator+(const point& rhs) const { return point(*this) += rhs; }
    point operator-(const point& rhs) const { return point(*this) -= rhs; }
    point operator*(const T& rhs) const { return point(*this) *= rhs; }
    point operator/(const T& rhs) const { return point(*this) /= rhs; }
    bool operator==(const point& rhs) const { return equal(x, rhs.x) && equal(y, rhs.y); }
    bool operator<(const point& rhs) const { return pair(x, y) < pair(rhs.x, rhs.y); }
};

template<typename T>
point<T> operator*(const T& a, const point<T>& p) { return p * a; }

template<typename T>
T dot(const point<T>& p, const point<T>& q) { return p.x * q.x + p.y * q.y; }

template<typename T>
T sqnorm(const point<T>& p) { return dot(p, p); }

template<typename T>
T norm(const point<T>& p) { return sqrt(dot(p, p)); }

template<typename T>
T proj(const point<T>& p, const point<T>& q) { return dot(p, q) / norm(q); }

template<typename T>
T angle(const point<T>& p, const point<T>& q) { return acos(dot(p / norm(p), q / norm(q))); }

template<typename T>
T det(const point<T>& p, const point<T>& q) { return p.x * q.y - p.y * q.x; }

template<typename T>
bool parallel(const point<T>& p, const point<T>& q)
{
    return equal(det(p, q), 0);
}

template<typename T>
point<T> intersection(const point<T>& p, const point<T>& dp, const point<T>& q, const point<T>& dq)
{
    return p + det(q - p, dq) / det(dp, dq) * dp;
}

template<typename T>
point<T> rotate(const point<T>& p, T theta) // counter-clockwise
{
    return point<T>(cos(theta) * p.x - sin(theta) * p.y, sin(theta) * p.x + cos(theta) * p.y);
}

template<typename T>
point<T> rotate(const point<T>& p) { return point<T>(-p.y, p.x); } // pi/2 rad counter-clockwise

template<typename T>
bool cw(const point<T>& p, const point<T>& q, const point<T>& r)
{
    return det(q - p, r - q) < 0;
}

template<typename T>
bool ccw(const point<T>& p, const point<T>& q, const point<T>& r)
{
    return det(q - p, r - q) > 0;
}

template<typename T>
vector<point<T>> convex_hull(vector<point<T>> a) // counter-clockwise
{
    sort(all(a)); a.erase(unique(all(a)), a.end());
    point<T> p = a[0], q = a.back();
    vector<point<T>> up = { p }, down = { p };
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
    line(const point<T>& p, const point<T>& q)
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
point<T> intersection(line<T> U, line<T> V)
{
    T x = -det({ U.c, U.b }, { V.c, V.b });
    T y = -det({ U.a, U.c }, { V.a, V.c });
    T z = det({ U.a, U.b }, { V.a, V.b });
    return point<T>(x / z, y / z);
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

