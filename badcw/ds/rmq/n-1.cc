#include <bits/stdc++.h>

// 0 index 2e7 random data, luogu P3793
template <class T, class Comp = std::greater<T>, int LOGN = 20, int BLOCK_MUL = 15>  
struct RMQ {
    std::vector<T> a;

    int  maxm{}, maxn{};
    int  n{}, block{};
    Comp comp;

    std::vector<int> belong{}, pos{}, lg{}, pow{};

    std::vector<std::array<T, LOGN>> s;

    std::vector<T> pre, sub;

    T min(const T& x, const T& y) {
        return comp(x, y) ? x : y;
    }

    void build_st() {
        int cur = 0, id = 1;
        pos[0] = -1;
        for (int i = 1; i <= n; ++i) {
            s[id][0]  = min(s[id][0], a[i]);
            belong[i] = id;
            if (belong[i - 1] != belong[i])
                pos[i] = 0;
            else
                pos[i] = pos[i - 1] + 1;
            if (++cur == block) {
                cur = 0;
                ++id;
            }
        }
        if (n % block == 0) --id;
        pow[0] = 1;
        for (int i = 1; i < maxm; ++i) pow[i] = pow[i - 1] * 2;
        for (int i = 2; i <= id; ++i) lg[i] = lg[i / 2] + 1;
        for (int i = 1; i <= lg[id]; ++i) {
            for (int j = 1; j + pow[i] - 1 <= id; ++j) { s[j][i] = min(s[j][i - 1], s[j + pow[i - 1]][i - 1]); }
        }
    }

    void build_sub_pre() {
        for (int i = 1; i <= n; ++i) {
            if (belong[i] != belong[i - 1])
                pre[i] = a[i];
            else
                pre[i] = min(pre[i - 1], a[i]);
        }
        for (int i = n; i >= 1; --i) {
            if (belong[i] != belong[i + 1])
                sub[i] = a[i];
            else
                sub[i] = min(sub[i + 1], a[i]);
        }
    }

    explicit RMQ(const std::vector<T>& a) {
        n     = a.size();
        block = std::max(int(log2(n) * BLOCK_MUL), 1);
        maxn  = n / block + 2;
        maxm  = log2(maxn) + 1;
        pow.resize(maxm);
        s.resize(maxn);
        pos.resize(n + 1), belong.resize(n + 1), lg.resize(n + 1), pre.resize(n + 1), sub.resize(n + 1),
            this->a.resize(n + 1);
        for (int i = 1; i <= n; ++i) this->a[i] = a[i - 1];
        build_st();
        build_sub_pre();
    }

    T query(int l, int r) {
        l++, r++;
        int bl = belong[l], br = belong[r];
        if (bl != br) {
            if (br - bl > 1) {
                int p = lg[br - bl - 1];
                return min(min(sub[l], pre[r]), min(s[bl + 1][p], s[br - pow[p]][p]));
            } else {
                return min(sub[l], pre[r]);
            }
        } else {
            return accumulate(a.begin() + l, a.begin() + r + 1, *(a.begin() + l), [&](T x, T y) { return min(x, y); });
        }
    }
};