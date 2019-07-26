| Date      | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |
| --------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 2019/7/24 | 6/12   |  .   |  .   |  .   |  .   |  O   |  .   |  .   |  Ø   |  Ø   |  O   |  Ø   |  Ø   |

## I、[I Love Palindrome String](https://cn.vjudge.net/contest/314097#problem/I)

题意：求所有长度为1～n的子串满足\(S_i^j\)和\(S_i^{i+j/2}\)为回文串的个数

题解：对所有回文串来说，它前半段是否是回文串都是确定是，所以回文树维护所有本质不同串，每增加一个节点就计算这个节点的前半段是否是回文串，可以直接上一手hash快速判断，然后如果是，该本质串的长度就要加个它个数的权值，最后整合起来即可，复杂度\(O(n)\)。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1009.cpp
*   创 建 者： badcw
*   创建日期： 19-7-25
*
================================================================*/
#include <bits/stdc++.h>
 
#define ll long long
using namespace std;
 
const int maxn = 3e5 + 5;
const int mod = 51123987;
ll qp(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
 
template <class T>
inline bool scan(T& ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; // EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
 
//template <class T>
//inline void out(T x) {
//    if (x > 9) out(x / 10);
//    putchar(x % 10 + '0');
//}

typedef unsigned long long ull;
struct mhash {
    ull base[maxn];
    ull hash_index[maxn];
    ull seed; //31, 131
    void inithash(ull seedt = 31) {
        base[0] = 1;
        seed = seedt;
        for (int i = 1; i < maxn; ++i) base[i] = base[i - 1] * seed;
    }
    void hash(char *p, int n) { // from 1 to n
        hash_index[0] = 0;
        for (int i = 1; i <= n; ++i) hash_index[i] = hash_index[i - 1] * seed + p[i] - 'a';
    }
    ull gethash(int s, int e) {
        return hash_index[e] - hash_index[s - 1] * base[e - s + 1];
    }
}pre, last;

int n;
char s[maxn];
char s1[maxn];

bool check(int l, int r) {
    return pre.gethash(l, r) == last.gethash(n - r + 1, n - l + 1) &&
        pre.gethash(l, (l + r) / 2) == last.gethash(n - (l + r) / 2 + 1, n - l + 1);
}

const int N = 26;

struct Palindromic_Tree {
//    vector<pair<int, int> > next[maxn];
    int ok[maxn];
    int next[maxn][N];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[maxn]{};//fail指针，失配后跳转到fail指针指向的节点
    int cnt[maxn]{}; //表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
    int num[maxn]{}; //表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[maxn]{};//len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串）
    int S[maxn]{};//存放添加的字符
    int last{};//指向新添加一个字母后所形成的最长回文串表示的节点。
    int n{};//表示添加的字符个数。
    int p{};//表示添加的节点个数。

    int newnode(int l) {//新建节点
//        next[p].clear();
        for (int i = 0; i < N; ++i) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }

    void init() {//初始化
        n = last = p = 0;
        newnode(0);
        newnode(-1);
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }

    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }

    int add(int c, int pos) {
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
//        int x = find(cur, c);
//        if (!x) {
        if (!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
//            x = now;
//            fail[now] = find(get_fail(fail[cur]), c);
//            next[cur].emplace_back(make_pair(c, now));
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
            ok[now] = check(pos - len[now] + 1, pos);
        }
//        last = x;
        last = next[cur][c];
        cnt[last]++;
        return num[last];
    }

    void count() {
        for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} solve;

int ttans[maxn];

int main(int argc, char* argv[]) {
    pre.inithash();
    last.inithash();
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) s1[n - i + 1] = s[i];
        pre.hash(s, n);
        last.hash(s1, n);
        solve.init();
        for (int i = 1; i <= n; ++i) solve.add(s[i] - 'a', i);
        solve.count();
        for (int i = 1; i <= n; ++i) ttans[i] = 0;
        for (int i = 2; i <= solve.p; ++i) {
            ttans[solve.len[i]] += solve.cnt[i] * solve.ok[i];
        }
        for (int i = 1; i <= n; ++i) printf("%d%c", ttans[i], i == n ? '\n' : ' ');
    }
    return 0;
}
```



## J、[Just Skip The Problem](https://cn.vjudge.net/problem/HDU-6600)

 题意：要确定一个2进制位为n的数x，求最少需要多少次询问，每次询问可以回答它&x是否为0。问所有的最少次数的方案数。

题解：推一推显然每次问它某个2进制位就行，最少n次，然后就是n个数的全排列，由于模数只有`1e6+3`，直接推前`1e6+3`项的阶乘，后面全是0即可。

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：J.cpp
*   创 建 者： badcw
*   创建日期： 19-7-25
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e6+4;
const int mod = 1e6+3;
ll qp(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

template <class T>
inline bool scan(T& ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; // EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

//template <class T>
//inline void out(T x) {
//    if (x > 9) out(x / 10);
//    putchar(x % 10 + '0');
//}

ll jie[maxn] = {1};

int main(int argc, char* argv[]) {
    for (int i = 1; i < maxn; ++i) jie[i] = jie[i - 1] * i % mod;
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%lld\n", n < maxn ? jie[n] : 0ll);
    }
    return 0;
}
```



## K、[Keen On Everything But Triangle](https://cn.vjudge.net/problem/HDU-6601)

 题意：给一个序列，求l到r中使用三个数字能组成的三角形中的最长周长。

题解：首先了解到这三条边必然是（数值大小上）相邻的三个。反证法易证，就直接是一定有更相邻的数可以使得答案更大，然后考虑从小到大不合法的方案，显然`1 1 2 3 5 8 ...`这个序列是最小的能构不成三角形的序列，而我们都知道斐波那契数列递增巨快，推出来大概44项就超过1e9了，然后就维护区间前44项大值即可。本来写了一波巨优美的线段树+莫队，然后就暴毙在莫队的根号复杂度下了。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1011.cpp
*   创 建 者： badcw
*   创建日期： 19-7-24
*
================================================================*/
#include <bits/stdc++.h>
 
#define ll long long
using namespace std;
 
const int maxn = 1e5+5;
const int mod = 1e9+7;
ll qp(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}
 
template <class T>
inline bool scan(T& ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; // EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}
 
//template <class T>
//inline void out(T x) {
//    if (x > 9) out(x / 10);
//    putchar(x % 10 + '0');
//}

int val[maxn<<2][45];
int a[maxn];
int res[45], tp[45];
int le, re, k;
int n, m;

inline void pushup(int *a, int *b) {
    int i = 0, j = 0, now = 0;
    while (now < 45) {
        if (a[i] > b[j]) {
            res[now++] = a[i++];
        } else res[now++] = b[j++];
    }
}

inline void build(int rt, int l, int r) {
    if (l == r) {
        val[rt][0] = a[l];
        for (int i = 1; i < 45; ++i) val[rt][i] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(val[rt << 1], val[rt << 1 | 1]);
    for (int i = 0; i < 45; ++i) val[rt][i] = res[i];
}

inline void query(int rt, int l, int r) {
    if (le <= l && r <= re) {
        pushup(tp, val[rt]);
        for (int i = 0; i < 45; ++i) tp[i] = res[i];
        return;
    }
    int mid = l + r >> 1;
    if (le <= mid) query(rt << 1, l, mid);
    if (re > mid) query(rt << 1 | 1, mid + 1, r);
}

int main(int argc, char* argv[]) {
//    freopen("data1.in", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        build(1, 1, n);
        while (m--) {
            scanf("%d%d", &le, &re);
            for (int i = 0; i < 45; ++i) tp[i] = 0;
            query(1, 1, n);
            ll tt = -1;
            for (int i = 0; i < 43; ++i) {
                if (tp[i + 2] == 0) break;
                if (tp[i + 1] + tp[i + 2] > tp[i]) {
                    tt = (ll)tp[i] + tp[i + 1] + tp[i + 2];
                    break;
                }
            }
            printf("%lld\n", tt);
//            fflush(stdout);
        }
    }
    return 0;
}
```



## L、[Longest Subarray](https://cn.vjudge.net/contest/314097#problem/L)
题意：给nck，表示序列长度为n，序列中元素集为c，要求最长的子序列使得序列中所有的元素个数要么是0要么不小于k。

题解：这也太容易去想dp解法了吧，然后发现复杂度能上天，c维dp。然后考虑维护对每个右端点每个数的能用的区间，显然除了右端点当前的值，其他值的区间与上一个右端点相同，多一个在当前区间能取，所以考虑线段树维护每个点能取多少个值，当前点首先加上c-1个值，然后考虑当前值的区间变化，一个是0区间被去掉了，所以从当前点值的上一个到当前点-1区间-1，再一个是当前点的前k个多了一个，所以从k-1到k区间+1，然后找最左边值为c的点与当前点作差更新答案，这个操作常用于线段树，实际上和单点查询一个复杂度。就是优先左儿子，如果左儿子有解直接返回结果，否则返回右儿子，实际上我维护最大值之后它有没有解很容易。这个题最好是维护一下每个点在哪出现，然后第一个出现的地方直接设为0，否则有点难以处理边界，我re了一面。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1012.cpp
*   创 建 者： badcw
*   创建日期： 19-7-24
*
================================================================*/
#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")

#define ll long long
using namespace std;

const int maxn = 1e5+5;
const int mod = 1e9+7;
ll qp(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

template <class T>
inline bool scan(T& ret) {
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; // EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

//template <class T>
//inline void out(T x) {
//    if (x > 9) out(x / 10);
//    putchar(x % 10 + '0');
//}

ll val[maxn<<2], lazy[maxn<<2];
int le, re;
vector<int> pos[maxn];
ll k;
int n, m, C;

inline void pushdown(int rt) {
    if (lazy[rt]) {
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        val[rt << 1] += lazy[rt];
        val[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

inline void build(int rt, int l, int r) {
    val[rt] = lazy[rt] = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
}

inline void update(int rt, int l, int r) {
    if (re < le || le <= 0) return;
    if (le <= l && r <= re) {
        val[rt] += k;
        lazy[rt] += k;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (le <= mid) update(rt << 1, l, mid);
    if (re > mid) update(rt << 1 | 1, mid + 1, r);
    val[rt] = max(val[rt << 1], val[rt << 1 | 1]);
}

inline int query(int rt, int l, int r) {
    if (val[rt] < C) return -1;
    if (l == r) {
        return l;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    int res = query(rt << 1, l, mid);
    if (res != -1) return res;
    return query(rt << 1 | 1, mid + 1, r);
}

int main() {
    while (scanf("%d%d%d", &n, &C, &m) != EOF) {
        for (int i = 1; i <= C; ++i) {
            pos[i].clear();
        }
        build(1, 1, n);
        int res = 0;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            le = re = i;
            k = C - 1;
            update(1, 1, n);
            if (pos[x].size()) le = pos[x].back() + 1;
            else le = 1;
            re = i - 1;
            k = -1;
            if (le <= re) update(1, 1, n);
            pos[x].push_back(i);
            int p = pos[x].size() - m - 1;
            if (p >= 0) {
                le = pos[x][p] + 1;
                re = pos[x][p + 1];
                k = 1;
                update(1, 1, n);
            } else if (p == -1 && !pos[x].empty()) {
                le = 1;
                re = pos[x][0];
                k = 1;
                update(1, 1, n);
            }
            int tmp = query(1, 1, n);
            if (tmp != -1) res = max(res, i - tmp + 1);
        }
        printf("%d\n", res);
    }
    return 0;
}
```

