// maintains maximum matching of minimum weight
template<typename T>
struct Hungarian {
    inline static const T inf = numeric_limits<T>::max();
    int N, M;
    T cost;
    vector<int> match;
    vector<T> ldual, rdual;
    vector<vector<T>> C;
    Hungarian(int N, int M) : N(N), M(M), cost(0), match(M, -1), ldual(N), rdual(M), C(N) {
        assert(N <= M);
    }
    void insert(int u, const vector<T>& row) {
        C[u] = row;
        ldual[u] = inf;
        for (int v = 0; v < M; ++v) {
            ldual[u] = min(ldual[u], C[u][v] - rdual[v]);
        }
        vector<T> dmin(M, inf);
        vector<int> best(M, -1);
        vector<bool> vis(M);
        int last = -1;
        for (int z = u; z != -1; z = match[last]) {
            T delta = inf;
            int next = -1;
            for (int v = 0; v < M; ++v) {
                if (vis[v]) continue;
                T d = C[z][v] - ldual[z] - rdual[v];
                if (d < dmin[v]) {
                    dmin[v] = d;
                    best[v] = last;
                }
                if (dmin[v] < delta) {
                    delta = dmin[v];
                    next = v;
                }
            }
            for (int v = 0; v < M; ++v) {
                if (vis[v]) {
                    ldual[match[v]] += delta;
                    rdual[v] -= delta;
                }
                else {
                    dmin[v] -= delta;
                }
            }
            ldual[u] += delta;
            last = next;
            vis[last] = true;
        }
        for (int v = last; v != -1; v = best[v]) {
            if (best[v] == -1) {
                match[v] = u;
            }
            else {
                int z = match[best[v]];
                cost -= C[z][best[v]];
                match[v] = z;
            }
            cost += C[match[v]][v];
        }
    }
};
