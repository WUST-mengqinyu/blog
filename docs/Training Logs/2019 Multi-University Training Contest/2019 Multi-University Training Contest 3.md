| Date      | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |
| --------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 2019/7/29 | 6/12   |  .   |  Ø   |  .   |  Ø   |  .   |  O   |  O   |  .   |  Ø   |  .   |  .   |



## [D - Distribution of books](https://cn.vjudge.net/problem/HDU-6606)

给一个序列，要求从前往后连续选m块，每块至少一个数，使得选取块的和最大值最小。

首先肯定是考虑二分的，直接二分答案就是能否选到m个不大于当前值的块即可。然后考虑怎么check，一个显然的\(O(n^2)\)的check是\(dp[i] = max(dp[j]) + 1 (\sum_{k=j}^i a[k] <= mid)\)，其实就已经很显然了，对每个dp值维护一个前缀dp权值线段树即可。

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1004.cpp
*   创 建 者： badcw
*   创建日期： 2019/7/29
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 2e5+5;
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

ll n, k;
ll a[maxn];
ll pre[maxn];
int val[maxn << 2];
vector<ll> xpos;
int sz;

void build(int rt, int l, int r) {
    val[rt] = -1000000000;
    if (l == r) return;
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
}

int le, re, kvalnow;

void update(int rt, int l, int r) {
    if (l == r) {
        val[rt] = max(val[rt], kvalnow);
        return;
    }
    int mid = l + r >> 1;
    if (le <= mid) update(rt << 1, l, mid);
    else update(rt << 1 | 1, mid + 1, r);
    val[rt] = max(val[rt << 1], val[rt << 1 | 1]);
}

int query(int rt, int l, int r) {
    if (le <= 0 || re < le) return -1000000000;
    if (le <= l && r <= re) {
        return val[rt];
    }
    int mid = l + r >> 1;
    int res = -1000000000;
    if (le <= mid) res = max(res, query(rt << 1, l, mid));
    if (re > mid) res = max(res, query(rt << 1 | 1, mid + 1, r));
    return res;
}

int dp[maxn];

inline bool check(ll mid) {
    build(1, 1, sz);
    le = lower_bound(xpos.begin(), xpos.end(), 0) - xpos.begin();
    kvalnow = 0;
    update(1, 1, sz);
    for (int i = 1; i <= n; ++i) {
        re = sz;
        le = lower_bound(xpos.begin(), xpos.end(), pre[i] - mid) - xpos.begin();
        int pos = lower_bound(xpos.begin(), xpos.end(), pre[i]) - xpos.begin();
//        if (xpos[re] != pre[i] - mid) re --;
        dp[i] = query(1, 1, sz) + 1;
        le = pos, kvalnow = dp[i];
//        cerr << le << " " << kvalnow << endl;
        update(1, 1, sz);
    }
    le = 1, re = sz;
    return query(1, 1, sz) >= k;
}

int main(int argc, char* argv[]) {
//    freopen("data.in", "r", stdin);
    int T;
//    scan(T);
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
//        scan(n), scan(k);
        scanf("%lld%lld", &n, &k);
        xpos.clear();
        xpos.push_back((ll)-2e14-100);
        xpos.push_back(0);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &a[i]);
            pre[i] = pre[i - 1] + a[i];
            xpos.push_back(pre[i]);
//            scan(a[i]);
//            scanf("%d", &a[i]);
        }
        sort(xpos.begin(), xpos.end());
        xpos.resize(unique(xpos.begin(), xpos.end()) - xpos.begin());
        xpos.push_back((ll)2e14+100);
        sz = xpos.size();
        check(2);
        ll mx = -1e9-100;
        for (int i = 1; i <= k; ++i) {
            mx = max(mx, a[i]);
        }
        ll l = -2e14-100, r = mx, res = r;
        while (l <= r) {
            ll mid = l + r >> 1;
//            cout << l << " " << r << " " << mid << endl;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
```



## [F - Fansblog](https://cn.vjudge.net/problem/HDU-6608)

求\(q! % p\)，其中pq都是素数且q是p的前一个素数，给p求值。

那么一个显然的结论\((q-1)!%q=1\)，然后就是相当于把`p+1~q-1`这段逆元乘回去即可，出于某种神奇的性质，`1e14`范围内素数之间距离没那么大，然后就可以`sqrt(n)`的处理每个数是不是素数直到枚举到前一个素数即可。还需要快速乘防止爆longlong有点恶心人。

代码：

```cpp
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1000;
const int mod = 1e9+7;

inline ll multi(ll a,ll n,ll p)
{
    ll re=0;
    while(n)
    {
        if(n&1) re=(re+a)%p;//做加法
        a=(a<<1)%p;
        n>>=1;
    }
    return re;
}

ll qp(ll a, ll n, ll m) {
    a %= m;
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = multi(res, a, m);
        a = multi(a, a, m);
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

bool pan(ll x) {
    for (ll i = 2; i * i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        ll q;
        scanf("%lld", &q);
        ll p = q - 1;
        while (!pan(p)) p --;
//        cerr << q << endl;
        ll res = q - 1;
        for (ll i = p + 1; i < q; ++i) {

            res = multi(res, qp(i, q - 2, q), q);
        }
        printf("%lld\n", res);
    }
    return 0;
}
```



## [G - Find the answer](https://cn.vjudge.net/problem/HDU-6609)

给一个序列和一个m值，求每个点必取的情况下，前面至少需要删掉多少个点才能让前缀和不超过m。

直接cf原题，数字的范围调大了点，我直接上了权值线段树维护前缀，然后树上二分，实际复杂度仍然是普通查找，求出权值线段树右方需要减掉多少个点能让前缀和变到m以内即可。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1007.cpp
*   创 建 者： badcw
*   创建日期： 2019/7/29
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 2e5+5;
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

struct node {
    int sum;
    ll valt;
    ll val;
}p[maxn << 2];

vector<int> xpos;
int le, k;

void build(int rt, int l, int r) {
    p[rt].sum = p[rt].val = 0;
    if (l == r) {
        p[rt].valt = xpos[l];
        return;
    }
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    p[rt].valt = min(p[rt << 1].valt, p[rt << 1 | 1].valt);
}

void update(int rt, int l, int r) {
    if (l == r) {
        p[rt].val += p[rt].valt;
        p[rt].sum ++;
        return;
    }
    int mid = l + r >> 1;
    if (le <= mid) update(rt << 1, l, mid);
    else update(rt << 1 | 1, mid + 1, r);
    p[rt].val = p[rt << 1].val + p[rt << 1 | 1].val;
    p[rt].sum = p[rt << 1].sum + p[rt << 1 | 1].sum;
}

int n, m;
int x[maxn];
ll need, gt;

void query(int rt, int l, int r) {
    if (p[rt].valt > need) return;
    if (p[rt].val <= need) {
        need -= p[rt].val;
        gt += p[rt].sum;
        return;
    }
    if (l == r) {
        if (need >= p[rt].val) need -= p[rt].val, gt += p[rt].sum;
        else {
            gt += need / p[rt].valt;
            need -= need / p[rt].valt * p[rt].valt;
        }
        return;
    }
    int mid = l + r >> 1;
    query(rt << 1, l, mid);
    query(rt << 1 | 1, mid + 1, r);
}

int main(int argc, char* argv[]) {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        xpos.clear();
        scanf("%d%d", &n, &m);
        xpos.push_back(0);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &x[i]);
            xpos.push_back(x[i]);
        }
        sort(xpos.begin(), xpos.end());
        xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
        int sz = xpos.size();
        build(1, 1, sz);
        for (int i = 1; i <= n; ++i) {
            need = m - x[i];
            gt = 0;
            query(1, 1, sz);
            printf("%lld ", i - gt - 1);
            le = lower_bound(xpos.begin(), xpos.end(), x[i]) - xpos.begin();
            update(1, 1, sz);
        }
        printf("\n");
    }
    return 0;
}
```

