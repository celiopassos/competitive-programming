// z-function from prefix function
vector<int> z_function(const vector<int>& p) {
    int N = (int)p.size() - 1;
    vector<int> z(N, 0);
    for (int len = 1; len <= N; ++len) {
        if (p[len]) {
            z[len - p[len]] = p[len];
        }
    }
    z[0] = N;
    for (int i = 1, last = 1; i < N; ++i) {
        if (i + z[i] > last + z[last]) last = i;
        z[i] = min(z[i - last], last + z[last] - i);
    }
    return z;
}
