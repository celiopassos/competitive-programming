class PalindromicTree {
private:
    const int alphabet = 26, N = 3e5;
    const vector<int> row = vector(alphabet, 0);
    int n = 1, sz = 2, last = 0;
    vector<int> s = vector(n, -1);
    vector<vector<int>> E = vector(sz, row);
    vector<int> len = vector(sz, 0);
    vector<int> link = vector(sz, 0);
    int get_link(int v) {
        while (s[((n - 1) - len[v]) - 1] != s[n - 1]) v = link[v];
        return v;
    }
public:
    PalindromicTree() {
        E.reserve(N), s.reserve(N), len.reserve(N), link.reserve(N);
        link[0] = 1, link[1] = 1;
        len[0] = 0, len[1] = -1;
    }
    void add_letter(char c) { add_letter(c - 'a'); }
    void add_letter(int c) {
        s.push_back(c); ++n;
        last = get_link(last);
        if (not E[last][c]) {
            len.push_back(len[last] + 2);
            link.push_back(E[get_link(link[last])][c]);
            E[last][c] = sz++;
            E.push_back(row);
        }
        last = E[last][c];
    }
    int size() const { return sz - 2; } // not counting empty
};
