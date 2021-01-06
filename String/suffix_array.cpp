int radix_sort(vector<int>& p, vector<int>& c, int shift, int k)
{
    static vector<int> pn, cn, cnt;
    const int n = size(p);
    pn.resize(n), cn.resize(n), cnt.resize(max(k, n));
    for (int i = 0; i < n; ++i)
    {
        pn[i] = p[i] - shift;
        if (pn[i] < 0) pn[i] += n;
    }
    fill(begin(cnt), begin(cnt) + k, 0);

    for (int i = 0; i < n; ++i) cnt[c[pn[i]]]++;
    for (int j = 1; j < k; ++j) cnt[j] += cnt[j - 1];
    for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];

    cn[p[0]] = 0, k = 1;
    for (int i = 1; i < n; ++i)
    {
        pair cur(c[p[i]], c[(p[i] + shift) % n]);
        pair prv(c[p[i - 1]], c[(p[i - 1] + shift) % n]);
        cn[p[i]] = (cur != prv ? ++k : k) - 1;
    }
    swap(c, cn);

    return k;
}

vector<int> sort_cyclic_shifts(const string& s)
{
    const int n = size(s), sigma = 256;

    vector p(n, 0), c(n, 0);

    iota(all(p), 0);

    for (int i = 0; i < n; ++i) c[i] = s[i];

    int k = radix_sort(p, c, 0, sigma);
    for (int h = 0; (1 << h) < n; ++h)
        k = radix_sort(p, c, 1 << h, k);

    return p;
}

auto suffix_array(string s)
{
    const int n = size(s);

    vector<int> p = sort_cyclic_shifts(s += char(0));
    p.erase(begin(p));

    vector<int> pos(n, 0);
    for (int i = 0; i < n; ++i) pos[p[i]] = i;

    return pair(p, pos);
}

vector<int> lcp_array(const string& s, const vector<int>& p, const vector<int>& pos)
{
    const int n = size(s);
    vector lcp(n - 1, 0);
    for (int i = 0, k = 0; i < n; ++i, k = max(0, k - 1))
    {
        if (pos[i] == n - 1) { k = 0; continue; }
        for (int j = p[pos[i] + 1]; max(i, j) + k < n && s[i + k] == s[j + k]; ++k);
        lcp[pos[i]] = k;
    }
    return lcp;
}

template<typename RMQ>
class SuffixArray
{
private:
    const pair<vector<int>, vector<int>> data;
    const vector<int> &p, &pos;
    const vector<int> lcp;
    const RMQ rmq;
public:
    SuffixArray(const string& s) :
        data(suffix_array(s)), p(data.first), pos(data.second),
        lcp(lcp_array(s, p, pos)), rmq(lcp) { }

    int operator[](int i) const { return p[i]; }
    int getpos(int i) const { return pos[i]; }
    int lcp_query(int i, int j) const
    {
        if (i == j) return size(p) - i;
        if (pos[i] > pos[j]) swap(i, j);
        return rmq.query(pos[i], pos[j] - 1);
    }
};
