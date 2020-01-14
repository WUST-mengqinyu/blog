## 早上讲课

Div2 数据结构，属实没有什么盐分，从栈到线段树

最大收货是明确了 Segment Beats 的复杂度是 O(nlogn)，可以放心的使用线段树进行区间推平操作

## 下午比赛

仍然在前 20 名，很多串和图题，还是有点难顶

## A. 托米的字符串

求所有子串中元音字母占比的平均值

显然 $ans=\sum{\frac{x}{len}}$，若对单点计算贡献，那么 $ans_i = \sum\frac{1}{len}$

考虑这样的情况

`(1------i----n)`

其中 `[1,i]` 长度为 `x`， `[i,n]` 长度为 `y`，设 $x \le y$ 显然对于 `[1,x]` 长度的串每个都有期望 1，然后对于 `[x+1,y]` 的串期望个数为 `x`。计算式为：$\sum_{i=x+1}^{y}\frac{x}{i}$，对于 `[y+1,x+y-1]` 的串期望为 `[x-1,1]` 计算式为：$\sum_{i=y+1}^{x+y-1}\frac{x+y-i}{i}$ 化简为 $x\cdot\sum_{i=y+1}^{x+y-1}\frac{1}{i}-\sum_{i=y+1}^{x+y-1}1$ 对于 $\frac{1}{i}$ 求前缀和即可

如果 $x > y$ 可以考虑交换，因为它们有对称性

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   创 建 者： badcw
*   创建日期： 2020/1/13
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e6+50;
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


struct Frac {
    ll a, b;
    void getJian() {
        ll gcd = abs(__gcd(a, b));
        a /= gcd;
        b /= gcd;
        if (b < 0) {
            a = -a;
            b = -b;
        }
    }
    Frac(ll a_ = 1, ll b_ = 1) {
        a = a_;
        b = b_;
        getJian();
    }
    Frac add(const Frac& oth) {
        ll bt = b * oth.b;
        ll at = a * oth.b + oth.a * b;
        return Frac(at, bt);
    }
    Frac multi(const Frac& oth) {
        a *= oth.a;
        b *= oth.b;
        getJian();
        return *this;
    }
    bool operator < (const Frac& oth) const {
        return a * oth.b < b * oth.a;
    }
    bool operator == (const Frac& oth) const {
        return a * oth.b == b * oth.a;
    }
    bool operator <= (const Frac& oth) const {
        return a * oth.b <= b * oth.a;
    }
};

char s[maxn];
double pre[maxn];
//double pre2[maxn];

int main(int argc, char* argv[]) {
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i) {
        pre[i] = pre[i - 1] + 1.0 / i;
//        pre2[i] = pre2[i - 1] + pre[i];
    }
    double res = 0;
    for (int i = 1; i <= len; ++i) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y') {
            int x = i;
            int y = len - i + 1;
//            res += x * pre[y] - pre2[x - 1];
            if (x > y) swap(x, y);
            res ++;
            res += x * (pre[y] - pre[x]);
            res += (x + y) * (pre[x + y - 1] - pre[y]);
//            res += (y - x) - x * (pre[y] - pre[x]);
        }
    }
    res /= len + (double)len * (len - 1) / 2;
    printf("%.10f\n", res);
    return 0;
}
```

## E. 阔力梯的树

给一颗带点权有根树

对于任意一颗子树定义它的结实程度为对它子树内所有节点的编号排序后获得数组 a, $\sum_{i=1}^{k-1}(a_{i+1}-a_i)^2$

显然考虑两个区间怎么合并，首先两个不交叉区间的元素不会互相影响权值，所以直接合并答案再加上边界的答案即可

直接考虑动态开点权值线段树合并即可

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   创 建 者： badcw
*   创建日期： 2020/1/13
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e5+50;
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

int root[maxn];
int ls[1800000], rs[1800000];
ll res[maxn];
int sz = 0;

struct node {
    int lnum, rnum;
    ll ans;
}p[1800000];

void pushup(int rt) {
    p[rt].ans = p[ls[rt]].ans + p[rs[rt]].ans;
    if (p[ls[rt]].lnum) p[rt].lnum = p[ls[rt]].lnum;
    else p[rt].lnum = p[rs[rt]].lnum;
    if (p[rs[rt]].rnum) p[rt].rnum = p[rs[rt]].rnum;
    else p[rt].rnum = p[ls[rt]].rnum;
    if (p[rs[rt]].lnum == 0 || p[ls[rt]].rnum == 0) return;
    p[rt].ans += (ll)(p[rs[rt]].lnum - p[ls[rt]].rnum) * (p[rs[rt]].lnum - p[ls[rt]].rnum);
}

void insert(int &k, int l, int r, int val){
    if (!k) k = ++sz;
    if (l == r) {
        p[k].lnum = p[k].rnum = val;
        p[k].ans = 0;
//        sum[k] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    if (val <= mid) insert(ls[k], l, mid, val);
    else insert(rs[k], mid + 1, r, val);
    pushup(k);
//    sum[k] = sum[ls[k]] + sum[rs[k]];
}

//int query(int k, int l, int r, int rank) {
//    if (l == r) return l;
//    int mid = (l + r) >> 1;
//    if (sum[ls[k]] >= rank) return query(ls[k], l, mid, rank);
//    else return query(rs[k], mid + 1, r, rank - sum[ls[k]]);
//}

int merge(int x, int y) {
    if (!x) return y;
    if (!y) return x;
    ls[x] = merge(ls[x], ls[y]);
    rs[x] = merge(rs[x], rs[y]);
    pushup(x);
//    sum[x] = sum[ls[x]] + sum[rs[x]];
    return x;
}

int n;
vector<int> edge[maxn];

void dfs(int u) {
    insert(root[u], 1, n, u);
    for (auto v : edge[u]) {
        dfs(v);
        merge(root[u], root[v]);
    }
    res[u] = p[root[u]].ans;
}

int main(int argc, char* argv[]) {
    scanf("%d", &n);
    for (int i = 2; i <= n; ++i) {
        int rt;
        scanf("%d", &rt);
        edge[rt].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        printf("%lld\n", res[i]);
    }
    return 0;
}
```