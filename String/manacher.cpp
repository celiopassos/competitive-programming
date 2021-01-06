auto odd
{
    int l = 0, r = -1, n = size(s);
    vector d(n, 0);
    for (int i = 0; i < n; ++i)
    {
        int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) ++k;
        d[i] = k--;
        if (i + k > r) l = i - k, r = i + k;
    }
    return d;
}

auto even(const string& s) // is this correct?? must test
{
    int n = size(s);
    string r; r.push_back('*');
    for (auto c : s) r.push_back(c), r.push_back('*');
    auto x = odd(r);
    vector d(n, 0);
    for (int i = 0; i < n; ++i)
        d[i] = x[2 * (i + 1)] / 2;
    return d; // d[i] = number of palindromes s[i - k, ..., i, i + 1, ..., i + 1 + k], i.e, i is left middle
}
