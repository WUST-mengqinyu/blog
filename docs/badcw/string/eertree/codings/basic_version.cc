#include <bits/stdc++.h>

/**
 * @brief 回文树
 * time: O(nlogm)
 * space: O(n)
 */
template <class T>
struct eertree {
    struct node {
        int len, fail;

        std::map<T, int> ch;

        void renew() {
            ch.clear();
        }
    };

    int cnt, last, n;

    std::vector<T>    s;
    std::vector<node> nd;

    eertree(int cap = 0) {
        n = 0;
        reserve(cap), init();
    }

    eertree(const std::basic_string<T>& _s) {
        n = _s.length();
        reserve(n), init();
        for (int i = 0; i < n; ++i) _s[i] = s[i], __extend(_s[i], i);
    }

    void init() {
        nd[0].len = 0, nd[0].fail = 1;
        nd[1].len = -1, nd[1].fail = 0;
        cnt  = 1;
        last = 0;
    }

    void reset() {
        last = n = 0;
    }

    int size() {
        return n;
    }

    int __getfail(int p, int k) {
        while (k - nd[p].len - 1 < 0 || s[k - nd[p].len - 1] != s[k]) p = nd[p].fail;
        return p;
    }

    void reserve(int cap) {
        if (n >= cap) return;
        s.resize(cap);
        nd.resize(cap + 2);
    }

    /**
     * @brief 往回文树末尾添加一个字符
     *
     * @param ch 添加的字符
     * @return int 新出现了多少个新的本质不同回文子串，实际只会是0/1
     */
    int extend(T ch, int ka) {
        s[n] = ch;
        return __extend(ch, n++, ka);
    }

    int __extend(T ch, int i, int ka) {
        int p = __getfail(last, i);
        if (nd[p].ch.find(ch) == nd[p].ch.end()) {
            cnt++;
            nd[cnt].renew();
            nd[cnt].fail = nd[__getfail(nd[p].fail, i)].ch[s[i]];
            nd[cnt].len  = nd[p].len + 2;
            last = nd[p].ch[s[i]] = cnt;
            return 1;
        } else {
            last = nd[p].ch[s[i]];
        }
        return 0;
    }
};