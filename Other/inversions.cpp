template<typename T>
long long merge_sort(vector<T>& v, vector<T>& aux, int l, int r) {
    if (r <= l) return 0LL;
    int m = l + (r - l) / 2;
    long long res = merge_sort(v, aux, l, m) + merge_sort(v, aux, m + 1, r);
    int x = l, y = m + 1, z = l;
    while (x <= m && y <= r) {
        aux[z++] = v[x] <= v[y] ? v[x++] : (res += m - x + 1, v[y++]);
    }
    while (x <= m) aux[z++] = v[x++];
    while (y <= r) aux[z++] = v[y++];
    while (l <= r) v[--z] = aux[r--];
    return res;
}
template<typename T>
long long inversions(vector<T> v) {
    static vector<T> aux;
    aux.resize(max(aux.size(), v.size()));
    return merge_sort(v, aux, 0, (int)v.size() - 1);
}
