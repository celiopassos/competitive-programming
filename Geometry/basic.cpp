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

bool equal(const T& a, const T& b) { return abs(a - b) < EPS; }

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
    bool operator==(const point& rhs) const { return equal(abs(x - rhs.x) + abs(y - rhs.y), 0); }
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

int main()
{ _
    exit(0);
}

