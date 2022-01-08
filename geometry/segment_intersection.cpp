template<typename T>
int sgn(T x) { return x >= 0 ? x > 0 ? +1 : 0 : -1; }
template<typename T>
bool intersects(T a, T b, T c, T d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}
template<typename T>
bool intersects(Segment<T> U, Segment<T> V) {
    auto [a, b] = U;
    auto [c, d] = V;
    if (cross(a - c, d - c) == 0 && cross(b - c, d - c) == 0) {
        return intersects(a.x(), b.x(), c.x(), d.x()) &&
            intersects(a.y(), b.y(), c.y(), d.y());
    } else {
        return sgn(cross(b - a, c - a)) != sgn(cross(b - a, d - a)) &&
            sgn(cross(d - c, a - c)) != sgn(cross(d - c, b - c));
    }
}
