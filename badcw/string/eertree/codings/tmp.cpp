/*================================================================
*
*   创 建 者： badcw
*   创建日期： 2022-08-19 22:42:29
*
================================================================*/
#include <bits/stdc++.h>
//#include "testlib.h"
//#include "atcoder/all"

#define VI vector<int>
#define ll long long
using namespace std;

// clang-format off
namespace IO {
    template<class T>
    void _R(T &x) { cin >> x; }
    void _R(int &x) { scanf("%d", &x); }
    void _R(ll &x) { scanf("%lld", &x); }
    void _R(double &x) { scanf("%lf", &x); }
    void _R(char &x) { x = getchar(); }
    void _R(char *x) { scanf("%s", x); }
    template<class T, class U>
    void _R(pair<T, U> &x) { _R(x.first), _R(x.second); }
    template<class T>
    void _R(vector<T> &x) { for(auto&i:x) _R(i); }
    void R() {}
    template<class T, class... U>
    void R(T &head, U &... tail) {_R(head),R(tail...);}
    template<class T>
    void _W(const T &x) { cout << x; }
    void _W(const int &x) { printf("%d", x); }
    void _W(const ll &x) { printf("%lld", x); }
    void _W(const double &x) { printf("%.16f", x); }
    void _W(const char &x) { putchar(x); }
    void _W(const char *x) { printf("%s", x); }
    template<class T, class U>
    void _W(const pair<T, U> &x) {_W(x.first),putchar(' '),_W(x.second);}
    template<class T>
    void _W(const set<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
    template<class T>
    void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
    void W() {}
    template<class T, class... U>
    void W(const T &head, const U &... tail) {_W(head),putchar(sizeof...(tail) ? ' ' : '\n'),W(tail...);}
}
using namespace IO;
// clang-format on


const int maxn = 3e5+50;
const int mod = 1e9+7;

ll qp(ll a, ll n) {
    ll res = 1;
    n %= mod - 1;
    if (n < 0) n += mod - 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll qp(ll a, ll n, int mod) {
    ll res = 1;
    n %= mod - 1;
    if (n < 0) n += mod - 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

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

char s[maxn];

int main(int argc, char **agrv) {
    int n; R(n);
    eertree<char> t(maxn);
    for (int i = 1; i <= n; ++i) {
        R(s);
        t.reset();
        for (int j = 0; s[j]; j++) t.extend(s[j], i);
        // W("*", t.cnt);
        // for (int j = 2; j <= t.cnt; ++j) printf("%d ", t.nd[j].lstp);
        // W(' ');
    }
    int res = 0;
    for (int i = 0; i <= t.cnt; ++i) {
        if (t.nd[i].lstp == n) res ++;
    }
    W(res);
    return 0;
}
