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
// z-function from prefix function
vector<int> z_function(const vector<int>& p) {
    int n = (int)size(p) - 1;
    vector<int> z(n, 0);
    for (int len = 1; len <= n; ++len) {
        if (p[len]) {
            z[len - p[len]] = p[len];
        }
    }
    z[0] = n;
    for (int i = 1, last = 1; i < n; ++i) {
        if (i + z[i] > last + z[last]) last = i;
        z[i] = min(z[i - last], last + z[last] - i);
    }
    return z;
}
