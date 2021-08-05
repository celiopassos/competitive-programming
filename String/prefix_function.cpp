vector<int> prefix_function(const string& s) {
    int N = (int)s.size();
    vector<int> p(N + 1, 0);
    for (int len = 2; len <= N; ++len) {
        int x = p[len - 1];
        while (x && s[len - 1] != s[x]) x = p[x];
        if (s[len - 1] == s[x]) ++x;
        p[len] = x;
    }
    return p;
}
