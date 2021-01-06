auto sieve(int N)
{
    vector<int> lp(N + 1, 0), pr;
    for (int i = 2; i <= N; ++i)
    {
        if (lp[i] == 0) pr.push_back(lp[i] = i);
        for (auto p : pr)
        {
            if (p > lp[i] || i * p > N) break;
            lp[i * p] = p;
        }
    }
    return pair(lp, pr);
}
