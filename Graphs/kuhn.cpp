int kuhn(int n, int m, const auto& E)
{
    vector<int> matchA(n, -1), matchB(m, -1), vis(m, 0);
    function<bool(int)> augment = [&](int u)
    {
        for (auto v : E[u])
        {
            if (vis[v]++) continue;
            if (matchB[v] == -1 || augment(matchB[v]))
            {
                matchA[u] = v, matchB[v] = u;
                return true;
            }
        }
        return false;
    };
    int ct = 0;
    while (true)
    {
        fill(all(vis), 0);
        bool aux = false;
        for (int u = 0; u < n; ++u)
            if (matchA[u] == -1 && augment(u)) ct += (aux = true);
        if (not aux) break;
    }
    return ct;
}
