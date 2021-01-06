template<int K = 26, char offset = 'a'>
struct SuffixAutomaton
{
    struct State
    {
        int link, len, minlen, idx;
        int nxt[K];
        bool terminal = false, clone = false;
        State(int link = -1, int len = 0) : link(link), len(len) { fill(all(nxt), -1); }
    };
    vector<State> state = { State() };

    int last = 0, total_size = 0;
    void extend(char c)
    {
        int cur = size(state), u = last, len = state[last].len + 1, ch = c - offset;

        for (;u != -1 && state[u].nxt[ch] == -1; u = state[u].link)
            state[u].nxt[ch] = cur;

        last = cur;

        if (u == -1)
        {
            state.emplace_back(0, len);
        }
        else if (int v = state[u].nxt[ch]; state[u].len + 1 == state[v].len)
        {
            state.emplace_back(v, len);
        }
        else
        {
            int clone = cur + 1;
            state.emplace_back(clone, len);
            state.push_back(state[v]);

            state[clone].len = state[u].len + 1, state[clone].clone = true;
            state[v].link = clone, state[v].minlen = state[clone].len + 1;

            for (int p = u; p != -1 && state[p].nxt[ch] == v; p = state[p].link)
                state[p].nxt[ch] = clone;
        }

        state[cur].minlen = state[state[cur].link].len + 1;
        state[cur].idx = total_size++;
    }

    SuffixAutomaton(const string& s)
    {
        for (auto c : s) extend(c);
        for (int v = last; v != -1; v = state[v].link)
            state[v].terminal = true;
    }

    int go(int u, char c) const
    {
        return state[u].nxt[c - offset];
    }
};
