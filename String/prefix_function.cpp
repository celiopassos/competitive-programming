vector<int> prefix_function(const string& s) {
    int n = (int)size(s);
    vector<int> p(n + 1, 0);
    for (int len = 2; len <= n; ++len) {
        int x = p[len - 1];
        while (x && s[len - 1] != s[x]) x = p[x];
        if (s[len - 1] == s[x]) ++x;
        p[len] = x;
    }
    return p;
}
