vector<int> prefix_function(const string& s) {
    int n = (int)size(s);
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) ++j;
        p[i] = j;
    }
    return p;
}
// z-function from prefix function
vector<int> z_function(const vector<int>& p) {
    int n = (int)size(p);
    vector<int> z(n, 0);
    for (int i = 0; i < n; ++i) {
        int j = i - p[i] + 1;
        if (p[i]) z[j] = p[i];
    }
    z[0] = n;
    for (int i = 1, last = 1; i < n; ++i) {
        if (i + z[i] > last + z[last]) last = i;
        z[i] = min(z[i - last], last + z[last] - i);
    }
    z[0] = 0;
    return z;
}
template<int K = 26, char offset = 'a'>
vector<array<int, K>> compute_automaton(string s) {
    s += offset + K;
    int n = (int)size(s);
    vector<int> p = prefix_function(s);
    vector<array<int, K>> aut(n);
    for (int i = 0; i < n; ++i)
        for (int c = 0; c < K; ++c) {
            if (i > 0 && offset + c != s[i])
                aut[i][c] = aut[p[i - 1]][c];
            else
                aut[i][c] = i + (offset + c == s[i]);
        }
    return aut;
}
