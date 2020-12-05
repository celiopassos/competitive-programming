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

// need to test everything...

using T = double;

const long double EPS = 1e-6;

bool Tcmp(const T& lhs, const T& rhs) { return lhs + EPS < rhs; }
bool Tequal(const T& lhs, const T& rhs) { return abs(lhs - rhs) <= EPS; }

struct Point
{
    T x, y;
    Point(T x = 0, T y = 0) : x(x), y(y) { }
    Point operator+=(const Point& rhs) { x += rhs.x, y += rhs.y; return *this; }
    Point operator-=(const Point& rhs) { x -= rhs.x, y -= rhs.y; return *this; }
    Point operator+(const Point& rhs) const { return Point(*this) += rhs; }
    Point operator-(const Point& rhs) const { return Point(*this) -= rhs; }
    friend Point operator*(const T& alpha, const Point& pt)
    {
        return Point(alpha * pt.x, alpha * pt.y);
    }
    friend T operator*(const Point& lhs, const Point& rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }
    bool operator<(const Point& rhs) const
    {
        return pair(x, y) < pair(rhs.x, rhs.y);
    }
    bool operator==(const Point& rhs) const
    {
        return Tequal(x, rhs.x) && Tequal(y, rhs.y);
    }
};

auto sq(auto x) { return x * x; }

T sqnorm(const Point& pt) { return pt * pt; }
T norm(const Point& pt) { return sqrt(sqnorm(pt)); }

T sqdist(const Point& p, const Point& q) { return sqnorm(p - q); }
T dist(const Point& p, const Point& q) { return sqrt(sqdist(p, q)); }

int sgn(T x) { return Tequal(x, T(0)) ? 0 : Tcmp(x, T(0)) ? -1 : +1; }

Point unit(const Point& pt) { return (T(1) / norm(pt)) * pt; }

// counter-clockwise

Point rotate(const Point& pt, double theta)
{
    double c = cos(theta), s = sin(theta);
    return Point(c * pt.x - s * pt.y, s * pt.x + c * pt.y);
}

Point rotate90(const Point& pt) { return Point(-pt.y, pt.x); }

// determinant of
// [ p.x p.y ]
// [ q.x q.y ]

T det(const Point& p, const Point& q)
{
    return p.x * q.y - q.x * p.y;
}

struct Line
{
    Point p, q;
    Line(Point p = Point(), Point q = Point()) : p(p), q(q) { }
    bool contains(Point pt) const
    {
        return Tequal(det(pt - p, q), T(0));
    }
    bool operator==(const Line& rhs) const
    {
        return contains(rhs.p) && contains(rhs.q);
    }
    bool operator!=(const Line& rhs) const { return not (*this == rhs); }
    T dist(Point pt) const
    {
        Point x = pt - p, y = q - p;

        Point proj = (x * y / sqnorm(y)) * y;

        return ::dist(x, proj);
    }
};

pair<bool, Point> intersection(const Line& U, const Line& V)
{
    if (U != V && Tequal(det(U.p - U.q, V.p - V.q), T(0)))
        return pair(false, Point());

    if (U == V) return pair(true, U.p);

    T alpha = det(U.p - V.p, V.p - V.q) / det(U.p - U.q, V.p - V.q);

    return pair(true, U.p + alpha * (U.q - U.p));
}

struct Segment
{
    Line L;
    Segment(Point p = Point(), Point q = Point()) : L(p, q) { }
    bool operator==(const Segment& rhs) const
    {
        return (L.p == rhs.L.p && L.q == rhs.L.q) || (L.q == rhs.L.p && L.p == rhs.L.q);
    }
    bool contains(Point pt) const
    {
        if (not L.contains(pt)) return false;

        Point x = pt - L.p, y = L.q - L.p;

        T alpha = T(1) / sqnorm(y) * x * y;

        return Tcmp(alpha, T(1 + EPS));
    }
    T dist(Point pt) const
    {
        Point x = pt - L.p, y = L.q - L.p;

        Point proj = L.p + (x * y / sqnorm(y)) * y;

        if (contains(proj))
            return ::dist(proj, pt);
        else
            return min(::dist(pt, L.p), ::dist(pt, L.q));
    }
};

pair<bool, Point> intersection(const Segment& U, const Segment& V)
{
    if (auto res = intersection(U.L, V.L); not res.first) return res;

    if (U.L == V.L)
    {
        for (auto pt : { U.L.p, U.L.q }) if (V.contains(pt)) return pair(true, pt);
        for (auto pt : { V.L.p, V.L.q }) if (U.contains(pt)) return pair(true, pt);
        return pair(false, Point());
    }
    else
    {
        Point pt = intersection(U.L, V.L).second;
        return pair(U.contains(pt) && V.contains(pt), pt);
    }
}

// check if p-q-r bends clockwise on q

bool cw(const Point& p, const Point& q, const Point& r)
{
    return Tcmp(det(q - p, r - q), T(0));
}

// check if p-q-r bends counter-clockwise on q

bool ccw(const Point& p, const Point& q, const Point& r)
{
    return Tcmp(T(0), det(q - p, r - q));
}

vector<Point> convex_hull(vector<Point> pts)
{
    sort(all(pts)), pts.erase(unique(all(pts)), end(pts));

    const int n = size(pts);

    Point p = pts[0], q = pts[n - 1];

    vector<Point> up = { p }, down = { p };

    for (int i = 1; i < n; ++i)
    {
        if (i == n - 1 || cw(p, pts[i], q))
        {
            while (size(up) > 1 && not cw(up[size(up) - 2], up[size(up) - 1], pts[i]))
                up.pop_back();
            up.push_back(pts[i]);
        }
        if (i == n - 1 || ccw(p, pts[i], q))
        {
            while (size(down) > 1 && not ccw(down[size(down) - 2], down[size(down) - 1], pts[i]))
                down.pop_back();
            down.push_back(pts[i]);
        }
    }

    up.pop_back(), reverse(all(up)), down.insert(end(down), all(up));

    return down;
}

bool is_inside(const vector<Point>& hull, Point pt)
{
    const int n = size(hull);

    if (n == 0) return false;
    if (n == 1) return pt == hull[0];
    if (n == 2) return Segment(hull[0], hull[1]).contains(pt);

    if (ccw(hull[0], hull[n - 1], pt)) return false;
    if (cw(hull[0], hull[1], pt)) return false;

    int split = 1;

    // split = largest i with cw(hull[0], hull[i], pt) == false;

    for (int z = n; z > 0; z >>= 1)
        while (split + z < n && not cw(hull[0], hull[split + z], pt)) split += z;

    if (split == n - 1) return true;

    return
        (not cw(hull[0], hull[split], pt)) &&
        (not cw(hull[split], hull[split + 1], pt)) &&
        (not cw(hull[split + 1], hull[0], pt));
}

int main()
{ _
    exit(0);
}
