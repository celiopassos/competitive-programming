template<typename T>
struct Beats {
    inline static const T linf = Clamp<T>::linf, rinf = Clamp<T>::rinf;
    struct Type {
        T sum, low[2], high[2];
        int cntlow, cnthigh;
        Type() : sum(0), low{rinf, rinf}, high{linf, linf}, cntlow(0), cnthigh(0) {}
        Type(T x) {
            sum = x;
            low[0] = x, low[1] = rinf;
            high[0] = x, high[1] = linf;
            cntlow = cnthigh = 1;
        }
    };
    inline static const Type Id = Type();
    static Type op(const Type& x, const Type& y) {
        Type res;
        res.sum = x.sum + y.sum;
        res.low[0] = min(x.low[0], y.low[0]);
        res.low[1] = min(x.low[x.low[0] == res.low[0]], y.low[y.low[0] == res.low[0]]);
        res.high[0] = max(x.high[0], y.high[0]);
        res.high[1] = max(x.high[x.high[0] == res.high[0]], y.high[y.high[0] == res.high[0]]);
        if (x.low[0] == res.low[0]) res.cntlow += x.cntlow;
        if (y.low[0] == res.low[0]) res.cntlow += y.cntlow;
        if (x.high[0] == res.high[0]) res.cnthigh += x.cnthigh;
        if (y.high[0] == res.high[0]) res.cnthigh += y.cnthigh;
        return res;
    }
    struct Node {
        Type value = Id;
        int l, r;
    };
    OffsetClamp<T> cl;
    Beats() {}
    Beats(T low, T high, T add) : cl(low, high, add) {}
    bool can_break(const Node& p) const {
        for (auto x : {p.value.low[0], p.value.high[0]}) {
            if (cl(x) != x) return false;
        }
        return true;
    }
    bool can_apply(const Node& p) const {
        auto& v = p.value;
        if (cl(v.low[0]) == cl(v.high[0])) return true;
        return cl(v.low[0]) != cl(v.low[1]) && cl(v.high[0]) != cl(v.high[1]);
    }
    void apply(Node& p) const {
        int len = p.r - p.l + 1;
        auto& [sum, low, high, cntlow, cnthigh] = p.value;
        if (cl(low[0]) == cl(high[0])) {
            T x = cl(high[0]);
            p.value = Type(x);
            sum = x * len;
            cntlow = cnthigh = len;
        }
        else {
            sum -= cntlow * low[0] + cnthigh * high[0];
            sum += cl.add * (len - cntlow - cnthigh);
            for (int t : {0, 1}) {
                low[t] = cl(low[t]);
                high[t] = cl(high[t]);
            }
            sum += cntlow * low[0] + cnthigh * high[0];
        }
    }
    void compose(Beats op) {
        cl = op.cl * cl;
    }
};
