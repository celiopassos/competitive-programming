string max_suffix(string s) {
    s += "#";
    string res; res.push_back(s[0]);
    for (int i = 1; i < (int)size(s); ++i) {
        int k = 0;
        while (k < (int)size(res) && s[i + k] == res[k]) ++k;
        if (s[i + k] > res[0])
            res = s.substr(i + k, 1);
        else if (k == (int)size(res) || s[i + k] < res[k])
            res += s.substr(i, k + 1);
        else
            res = s.substr(i, k + 1);
        i += k;
    }
    res.pop_back();
    return res;
}
