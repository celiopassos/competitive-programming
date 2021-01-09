auto prefix_function(const string& s)
{
    int n = size(s);
    vector<int> p(n, 0);
    for (int i = 1; i < n; ++i)
    {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) ++j;
        p[i] = j;
    }
    return p;
}

template<int K = 26, char offset = 'a'>
vector<array<int, K>> compute_automaton(string s)
{
    s += offset + K;
    int n = size(s);
    vector<int> p = prefix_function(s);
    vector<array<int, K>> aut(n);
    for (int i = 0; i < n; ++i)
        for (int c = 0; c < K; ++c)
        {
            if (i > 0 && offset + c != s[i])
                aut[i][c] = aut[p[i - 1]][c];
            else
                aut[i][c] = i + (offset + c == s[i]);
        }
    return aut;
}
