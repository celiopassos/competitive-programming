template<typename T>
ll merge_sort(vector<T>& v, vector<T>& aux, int l, int r)
{
    if (r <= l) return 0LL;
    int m = l + (r - l) / 2;
    ll res = merge_sort(v, aux, l, m) + merge_sort(v, aux, m + 1, r);
    int x = l, y = m + 1, z = l;
    while (x <= m && y <= r)
    {
        if (v[x] <= v[y])
            aux[z++] = v[x++];
        else
            aux[z++] = v[y++], res += m - x + 1;
    }
    while (x <= m) aux[z++] = v[x++];
    while (y <= r) aux[z++] = v[y++];
    while (l <= r) v[--z] = aux[r--];
    return res;
}

template<typename T>
ll inversions(vector<T> v)
{
    static vector<T> aux;
    aux.resize(max(size(aux), size(v)));
    return merge_sort(v, aux, 0, size(v) - 1);
}
