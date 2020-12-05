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

// Tested:
//
// [*] Line intersection
// [ ] Line-Point distance
// [ ] Line-Point containment
// [ ] Segment intersection
// [ ] Segment-Point distance
// [*] Segment-Point containment
// [*] Convex hull
// [*] is_inside

using T = double;

const long double EPS = 1e-4;

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
    bool operator!=(const Point& rhs) const { return not (*this == rhs); }
    friend ostream& operator<<(ostream& out, const Point& pt)
    {
        return out << pt.x << " " << pt.y;
    }
};

T sq(const T& x) { return x * x; }

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
        return Tequal(det(pt - p, q - p), T(0));
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

        T alpha = x * y / sqnorm(y);

        return not Tcmp(T(1), alpha);
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
    auto [good, p] = intersection(U.L, V.L);

    if (not good) return pair(false, Point());

    if (U.L == V.L)
    {
        for (auto q : { U.L.p, U.L.q }) if (V.contains(q)) return pair(true, q);
        for (auto q : { V.L.p, V.L.q }) if (U.contains(q)) return pair(true, q);
        return pair(false, Point());
    }
    else
    {
        return pair(U.contains(p) && V.contains(p), p);
    }
}

// checks if p-q-r bends clockwise on q

bool cw(const Point& p, const Point& q, const Point& r)
{
    return Tcmp(det(q - p, r - q), T(0));
}

// checks if p-q-r bends counter-clockwise on q

bool ccw(const Point& p, const Point& q, const Point& r)
{
    return Tcmp(T(0), det(q - p, r - q));
}

// O(n log(n))

vector<Point> convex_hull(vector<Point> pts)
{
    sort(all(pts)), pts.erase(unique(all(pts)), end(pts));

    const int n = size(pts);

    if (n == 1) return pts;

    Point p = pts[0], q = pts[n - 1];

    vector<Point> up(n), down(n); up[0] = down[0] = p;

    int idx = 1, idy = 1;

    for (int i = 1; i < n; ++i)
    {
        if (i == n - 1 || cw(p, pts[i], q))
        {
            while (idx > 1 && not cw(up[idx - 2], up[idx - 1], pts[i])) --idx;
            up[idx++] = pts[i];
        }
        if (i == n - 1 || ccw(p, pts[i], q))
        {
            while (idy > 1 && not ccw(down[idy - 2], down[idy - 1], pts[i])) --idy;
            down[idy++] = pts[i];
        }
    }

    up.resize(--idx), down.resize(idx + idy - 1);
    copy(rbegin(up), prev(rend(up)), begin(down) + idy);

    return down;
}

// if strictly == false,    checks if pt is contained in the convex hull
// if strictly == true,     checks if pt is in the relative interior
//
// assumes that hull is given in counter-clockwise
//
// if you want simply interior instead of relative interior, change it
// to return false if n < 3, because the interior is then empty
//
// O(log(size(hull)))

bool is_inside(const vector<Point>& hull, Point pt, bool strictly)
{
    const int n = size(hull);

    if (n == 0) return false;
    if (n == 1) return not strictly && pt == hull[0];
    if (n == 2) return
        Segment(hull[0], hull[1]).contains(pt) &&
        (not strictly || (hull[0] != pt && hull[1] != pt));

    if (ccw(hull[0], hull[n - 1], pt)) return false;
    if (cw(hull[0], hull[1], pt)) return false;

    int split = 1;

    for (int z = n; z > 0; z >>= 1)
        while (split + z < n && not cw(hull[0], hull[split + z], pt)) split += z;

    if (split == n - 1) return not strictly;

    int P[3] = { 0, split, split + 1 };

    for (int i = 0; i < 3; ++i)
    {
        int cur = P[i], nxt = P[(i + 1) % 3];

        if (cw(hull[cur], hull[nxt], pt)) return false;

        if (strictly && (cur + 1 - nxt) % n == 0 &&
            Segment(hull[cur], hull[nxt]).contains(pt)) return false;
    }

    return true;
}

int main()
{ _
    exit(0);
}
