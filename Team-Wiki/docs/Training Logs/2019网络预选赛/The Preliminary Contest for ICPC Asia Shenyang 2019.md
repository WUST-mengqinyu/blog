| Name                                                         | Date      | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |
| ------------------------------------------------------------ | --------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [The Preliminary Contest for ICPC Asia Shenyang 2019](https://www.jisuanke.com/contest/3007?view=challenges) | 2019/9/14 | 6/11   |  .   |  Ø   |  O   |  O   |  .   |  O   |  .   |  O   |  .   |  .   |  O   |

## tag

`#背包（c） #换根树dp（d） #点分治 （d） #并查集（b） ＃二分（ｆ） #矩阵快速幂（g） #高斯消元（g）`



## B、Dudu's maze

题意：给一张图，有一些关键点，在关键点外可以随意走动（起点为1且不是关键点），第一次到达关键点会随机向相邻点走动，第二次到达关键点就停止，求最多能到的非关键点的期望值（就是说会以最优的方式走动）。

题解：1的联通块都可以走完，与1这个块相连的关键点中取期望最大的就可以了。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：B.cpp
*   创 建 者： badcw
*   创建日期： 9/14/19
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

int pre[maxn];
int sz[maxn];
int u[maxn * 2], v[maxn * 2];
int vis[maxn];
int flag[maxn];
vector<int> edge[maxn];
int n, m, k;
double res;
int www;

inline int F(int x) {return x == pre[x] ? x : pre[x] = F(pre[x]);}

inline void dfs(int u) {
    vis[u] = 1;
    if (!flag[u]) {
        for (auto v : edge[u]) {
            if (vis[v]) continue;
            dfs(v);
        }
    } else {
        www = 1;
        double tmp = 0;
        for (auto v : edge[u]) {
            if (F(v) != F(1)) tmp += sz[F(v)];
        }
        tmp /= edge[u].size();
        res = max(res, tmp);
    }
}

int main(int argc, char* argv[]) {
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
//    clock_t ST = clock();
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%d%d%d", &n, &m, &k);
        www = 0;
        for (int i = 1; i <= n; ++i) {
            pre[i] = i;
            sz[i] = 1;
            vis[i] = 0;
            edge[i].clear();
            flag[i] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d", &u[i], &v[i]);
            edge[u[i]].push_back(v[i]);
            edge[v[i]].push_back(u[i]);
        }
        for (int i = 1, x; i <= k; ++i) {
            scanf("%d", &x);
            flag[x] = 1;
            sz[x] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            if (flag[u[i]] || flag[v[i]]) continue;
            int x = F(u[i]), y = F(v[i]);
            if (x != y) {
                sz[y] += sz[x];
                pre[x] = y;
            }
        }
        res = 0;
        dfs(1);
        if (www == 0) {
            printf("%.10f\n", (double)sz[F(1)]);
            continue;
        }
        printf("%.10f\n", res + sz[F(1)]);
    }
//    cerr << "time: " << ((clock() - ST) * 1000.0 / CLOCKS_PER_SEC) << "ms" << endl;
    return 0;
}
```

赛中判该点是不是1的联通点写了个蠢`F(v) != 1`，实际上并查集也没有特殊处理过。。。名额没了。



##  C. Dawn-K's water

题意：n种物品，每种物品有价值p和重量c，询问求最少要多少钱可以买至少m重量的物品。求出真正买的重量和花费。

题解：显然完全背包问题，由于最终价值不大于1e4，直接完全背包求到2e4肯定有解。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：C.cpp
*   创 建 者： badcw
*   创建日期： 9/14/19
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e3+5;
const int maxm = 2e4+5;
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

int n;
struct node {
    int p, c;
}a[maxn];

ll dp[maxm];

int main(int argc, char* argv[]) {
    int m;
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &a[i].p, &a[i].c);
        }
        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = a[i].c; j < maxm; ++j) {
                dp[j] = min(dp[j], dp[j - a[i].c] + a[i].p);
            }
        }
        ll INF = 0x3f3f3f3f3f3f3f3f;
        ll mnp = INF, mnc = INF;
        for (int i = m; i < maxm; ++i) {
            if (mnp >= dp[i]) {
                mnp = dp[i];
                mnc = i;
            }
        }
        printf("%lld %lld\n", mnp, mnc);
    }
    return 0;
}
```



## D、Fish eating fruit

题意：求一棵树上边权模3分别为0，1，2的边权和是多少

题解：数据范围较小爆上一个点分治即可，每次统计出过rt模3的边分别为0,1,2的边个数和总和，组合一下就能求出解。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：D.cpp
*   创 建 者： badcw
*   创建日期： 9/14/19
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e4+5;
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

int n;

// 清零 head 和 tot
const int maxm = 2e4+5;
int ver[maxm], Next[maxm], head[maxn], edge[maxm];
int tot;
void addEdge(int u, int v, int w){
    ver[++tot]=v;
    Next[tot]=head[u];
    head[u]=tot;
    edge[tot]=w;
}

int sz[maxn], vis[maxn];
int rt, mxsz, has;

inline void getrt(int u, int pre) {
    sz[u] = 1;
    int mxnow = 0;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == pre || vis[v]) continue;
        getrt(v, u);
        sz[u] += sz[v];
        mxnow = max(mxnow, sz[v]);
    }
    mxnow = max(mxnow, has - sz[u]);
    if (mxnow < mxsz) {
        mxsz = mxnow, rt = u;
    }
}

int dl[3], H[3];
int val[maxn];

inline void getdis(int u, int pre) {
    dl[val[u] % 3] = (dl[val[u] % 3] + val[u]) % mod;
    H[val[u] % 3] ++;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (v == pre || vis[v]) continue;
        val[v] = val[u] + edge[i];
        getdis(v, u);
    }
}

struct node {
    ll res[3];
    node operator + (const node& oth) {
        for (int i = 0; i < 3; ++i) {
            res[i] = (res[i] + oth.res[i]) % mod;
        }
        return *this;
    }
    node operator - (const node& oth) {
        for (int i = 0; i < 3; ++i) {
            res[i] = (res[i] - oth.res[i]) % mod;
        }
        return *this;
    }
    void cl() {
        for (int i = 0; i < 3; ++i) res[i] = 0;
    }
};

inline node cal(int u, int pre) {
    for (int i = 0; i < 3; ++i) dl[i] = 0, H[i] = 0;
    val[u] = pre;
    getdis(u, 0);
    node sum;
    sum.cl();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            sum.res[(i + j) % 3] += ((ll)(H[j]) * dl[i] % mod + (ll)H[i] * dl[j] % mod) % mod;
            sum.res[(i + j) % 3] %= mod;
        }
    }
    return sum;
}

node res;
inline void dfs(int u) {
//    printf("%d :%lld\n", u, cal(u, 0).res[0]);
    res = res + cal(u, 0);
    vis[u] = 1;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (vis[v]) continue;
//        printf("%d :-%lld\n", v, cal(v, edge[i]).res[0]);
        res = res - cal(v, edge[i]);
        has = sz[v];
        mxsz = 0x3f3f3f3f;
        getrt(v, 0);
        dfs(rt);
    }
}

int main(int argc, char* argv[]) {
    while (scanf("%d", &n) != EOF) {
        tot = 0; memset(head, 0, sizeof head);
        res.cl();
        memset(vis, 0, sizeof vis);
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            u ++;
            v ++;
            addEdge(u, v, w);
            addEdge(v, u, w);
//            cout << u << " " << v << " " << w << endl;
//            assert(v > 10000);
        }
        mxsz = 0x3f3f3f3f;
        has = n;
        getrt(1, 0);
        dfs(rt);
        printf("%lld %lld %lld\n", (mod + res.res[0]) % mod, (mod + res.res[1]) % mod, (mod + res.res[2]) % mod);
    }
    return 0;
}
```

题解2：树形dp换根求解。显然对某个点的答案可以`O(n)`求解，换根时同样记录子树中0,1,2的路径个数和总和即可。复杂度比点分治低，为`O(n)`。

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：D.cpp
*   创 建 者： badcw
*   创建日期： 9/17/19
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e4 + 5;
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

int n;
vector<pair<int, int> > edge[maxn];
ll dp[maxn][3]; // 每个点的答案
ll num[maxn][3]; // 每个点的答案数量
ll res[3];

inline void cal(int u) {
    for (int i = 0; i < 3; ++i) {
        (res[i] += dp[u][i]) %= mod;
    }
}

inline void dfs1(int u, int pre, ll len) {
    for (auto i : edge[u]) {
        int v = i.first;
        int w = i.second;
        if (v == pre) continue;
        dfs1(v, u, len + w);
        num[v][0] ++;
        for (int j = 0; j < 3; ++j) {
            dp[u][(j + w) % 3] += num[v][j] * w + dp[v][j];
            num[u][(j + w) % 3] += num[v][j];
        }
    }
}

inline void dfs2(int u, int pre) {
    cal(u);
    for (auto i : edge[u]) {
        int v = i.first;
        int w = i.second;
        if (v == pre) continue;
        ll dptmp[3], dptmp2[3];
        ll numtmp[3], numtmp2[3];
        for (int j = 0; j < 3; ++j) {
            dptmp[j] = dp[u][j];
            dptmp2[j] = dp[v][j];
            numtmp[j] = num[u][j];
            numtmp2[j] = num[v][j];
        }

        for (int j = 0; j < 3; ++j) {
            dp[u][(j + w) % 3] -= num[v][j] * w + dp[v][j];
            num[u][(j + w) % 3] -= num[v][j];
        }
        num[v][0] --;

        num[u][0] ++;
        for (int j = 0; j < 3; ++j) {
            dp[v][(j + w) % 3] += num[u][j] * w + dp[u][j];
            num[v][(j + w) % 3] += num[u][j];
        }
        dfs2(v, u);
        for (int j = 0; j < 3; ++j) {
            dp[u][j] = dptmp[j];
            dp[v][j] = dptmp2[j];
            num[u][j] = numtmp[j];
            num[v][j] = numtmp2[j];
        }
    }
}

int main(int argc, char* argv[]) {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < 3; ++i) res[i] = 0;
        for (int i = 1; i <= n; ++i) {
            edge[i].clear();
            for (int j = 0; j < 3; ++j) dp[i][j] = num[i][j] = 0;
        }
        for (int i = 1, u, v, w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            u ++, v ++;
            edge[u].push_back(make_pair(v, w));
            edge[v].push_back(make_pair(u, w));
        }
        dfs1(1, 0, 0);
        dfs2(1, 0);
        printf("%lld %lld %lld\n", res[0], res[1], res[2]);
    }
    return 0;
}
```



##　Ｆ、Honk's pool



## Ｈ、Texas hold'em Poker

题意：德州扑克比大小

题解：按题意模拟

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct player
{
    char name[15];
    int poker[5];
}p[maxn];
char card[15];
bool RoyalStraight(player a)
{
    if(a.poker[1]==10&&a.poker[2]==11&&a.poker[3]==12&&a.poker[4]==13&&a.poker[0]==1)
        return true;
    return false;
}
bool Straight(player a)
{
    for(int i=1;i<5;i++)
    {
        if(a.poker[i]-a.poker[i-1]!=1)
            return false;
    }
    return true;
}
bool Pair(player a)
{
    for(int i=0;i<4;i++)
    {
        if(a.poker[i]==a.poker[i+1])
            return true;
    }
    return false;
}
bool TwoPairs(player a)
{
    int tot=0;
    for(int i=0;i<4;i++)
    {
        if(a.poker[i]==a.poker[i+1])
            tot++;
    }
    return tot==2;
}
bool Three(player a)
{
    for(int i=0;i<3;i++)
    {
        if(a.poker[i]==a.poker[i+1]&&a.poker[i]==a.poker[i+2])
            return true;
    }
    return false;
}
bool Four(player a)
{
    for(int i=0;i<2;i++)
    {
        if(a.poker[i]==a.poker[i+1]&&a.poker[i]==a.poker[i+2]&&a.poker[i]==a.poker[i+3])
            return true;
    }
    return false;
}
bool FullHouse(player a)
{
    int cnt;
    bool f1=false,f2=false;
    for(int i=0;i<5;i++)
    {
        cnt=0;
        for(int j=0;j<5;j++)
        {
            if(a.poker[i]==a.poker[j])
                cnt++;
        }
        if(cnt==3) f1=true;
        if(cnt==2) f2=true;
    }
    return f1&&f2;
}
bool cmp(player a,player b)
{
    bool f1=RoyalStraight(a),f2=RoyalStraight(b);
    if(f1==true&&f2==true) return strcmp(a.name,b.name)<0;
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=Straight(a);
    f2=Straight(b);
    if(f1==true&&f2==true)
    {
        if(a.poker[4]==b.poker[4]) return strcmp(a.name,b.name)<0;
        return a.poker[4]>b.poker[4];
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=Four(a);
    f2=Four(b);
    if(f1==true&&f2==true)
    {
        int n1,n2,m1,m2;
        if(a.poker[0]==a.poker[1])
        {
            n1=a.poker[0];
            n2=a.poker[4];
        }
        else
        {
            n1=a.poker[4];
            n2=a.poker[0];
        }
        if(b.poker[0]==b.poker[1])
        {
            m1=b.poker[0];
            m2=b.poker[4];
        }
        else
        {
            m1=b.poker[4];
            m2=b.poker[0];
        }
        if(n1==m1)
        {
            if(n2==m2)
                return strcmp(a.name,b.name)<0;
            else
                return n2>m2;
        }
        else
            return n1>m1;
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=FullHouse(a);
    f2=FullHouse(b);
    if(f1==true&&f2==true)
    {
        int n1,n2,m1,m2;
        int cnt=0;
        for(int i=0;i<5;i++)
        {
            if(a.poker[i]==a.poker[0]) cnt++;
        }
        if(cnt==3)
        {
            n1=a.poker[0];n2=a.poker[4];
        }
        else
        {
            n1=a.poker[4];n2=a.poker[0];
        }
        cnt=0;
        for(int i=0;i<5;i++)
        {
            if(b.poker[i]==b.poker[0]) cnt++;
        }
        if(cnt==3)
        {
            m1=b.poker[0];m2=b.poker[4];
        }
        else
        {
            m1=b.poker[4];m2=b.poker[0];
        }
        if(n1==m1)
        {
            if(n2==m2)
                return strcmp(a.name,b.name)<0;
            else
                return n2>m2;
        }
        else
            return n1>m1;
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=Three(a);
    f2=Three(b);
    if(f1==true&&f2==true)
    {
        int n1,n2,m1,m2;
        int cnt;
        for(int i=0;i<5;i++)
        {
            cnt=0;
            n2=0;
            for(int j=0;j<5;j++)
            {
                if(a.poker[i]==a.poker[j])
                    cnt++;
                else
                    n2+=a.poker[j];
            }
            if(cnt==3)
            {
                n1=a.poker[i];
                break;
            }
        }
        for(int i=0;i<5;i++)
        {
            cnt=0;
            m2=0;
            for(int j=0;j<5;j++)
            {
                if(b.poker[i]==b.poker[j])
                    cnt++;
                else
                    m2+=b.poker[j];
            }
            if(cnt==3)
            {
                m1=b.poker[i];
                break;
            }
        }
        if(n1==m1)
        {
            if(n2==m2)
                return strcmp(a.name,b.name)<0;
            else
                return n2>m2;
        }
        else
            return n1>m1;
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=TwoPairs(a);
    f2=TwoPairs(b);
    if(f1==true&&f2==true)
    {
        int n1=-1,n2,n3,m1=-1,m2,m3;
        for(int i=0;i<5;i++)
        {
            if(i==4){
                n3=a.poker[4];
                break;
            }
            if(a.poker[i]==a.poker[i+1])
            {
                if(n1==-1)
                    n1=a.poker[i];
                else
                    n2=a.poker[i];
                i++;
            }
            else
                n3=a.poker[i];
        }
        for(int i=0;i<5;i++)
        {
            if(i==4)
            {
                m3=b.poker[4];
                break;
            }
            if(b.poker[i]==b.poker[i+1])
            {
                if(m1==-1)
                    m1=b.poker[i];
                else
                    m2=b.poker[i];
                i++;
            }
            else
                m3=b.poker[i];
        }
        if(n1<n2) swap(n1,n2);
        if(m1<m2) swap(m1,m2);
        if(n1==m1)
        {
            if(n2==m2)
            {
                if(n3==m3)
                    return strcmp(a.name,b.name)<0;
                else
                    return n3>m3;
            }
            else
                return n2>m2;
        }
        else
            return n1>m1;
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    f1=Pair(a);
    f2=Pair(b);
    if(f1==true&&f2==true)
    {
        int n1,n2,m1,m2,cnt;
        for(int i=0;i<5;i++)
        {
            cnt=0;
            n2=0;
            for(int j=0;j<5;j++)
            {
                if(a.poker[i]==a.poker[j])
                    cnt++;
                else
                    n2+=a.poker[j];
            }
            if(cnt==2)
            {
                n1=a.poker[i];
                break;
            }
        }
        for(int i=0;i<5;i++)
        {
            cnt=0;
            m2=0;
            for(int j=0;j<5;j++)
            {
                if(b.poker[i]==b.poker[j])
                    cnt++;
                else
                    m2+=b.poker[j];
            }
            if(cnt==2)
            {
                m1=b.poker[i];
                break;
            }
        }
        if(n1==m1)
        {
            if(n2==m2)
                return strcmp(a.name,b.name)<0;
            else
                return n2>m2;
        }
        else
            return n1>m1;
    }
    if(f1==true&&f2==false) return true;
    if(f1==false&&f2==true) return false;
    int sum1=0,sum2=0;
    for(int i=0;i<5;i++)
    {
        sum1+=a.poker[i];
        sum2+=b.poker[i];
    }
    if(sum1==sum2)
        return strcmp(a.name,b.name)<0;
    else
        return sum1>sum2;
}
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        for(int i=1;i<=n;i++)
        {
            scanf("%s%s",&p[i].name,&card);
            int len=strlen(card);
            int now=0;
            for(int j=0;j<len;j++)
            {
                if(card[j]>='2'&&card[j]<='9')
                {
                    p[i].poker[now++]=card[j]-'0';
                    continue;
                }
                if(card[j]=='A')
                {
                    p[i].poker[now++]=1;
                    continue;
                }
                if(card[j]=='J')
                {
                    p[i].poker[now++]=11;
                    continue;
                }
                if(card[j]=='Q')
                {
                    p[i].poker[now++]=12;
                    continue;
                }
                if(card[j]=='K')
                {
                    p[i].poker[now++]=13;
                    continue;
                }
                p[i].poker[now++]=10;
                j++;
            }
            sort(p[i].poker,p[i].poker+5);
        }
        sort(p+1,p+1+n,cmp);
        for(int i=1;i<=n;i++)
            printf("%s\n",p[i].name);
    }
    return 0;
}
```

## K、Guanguan's Happy water

题意：已知前2×k项，已知每一项只与前k项有关且是固定系数且保证结果为整数，即
$$
f_i = \sum_{j=1}^{k} a_j * f_{i-j}
$$
其中`a[j]`的和为1

题解：高斯消元求出a数组，然后矩阵快速幂即可，由于答案要求
$$
\sum_{i=1}^n f_i
$$
给快速幂加一维答案就可以了

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int mod = 1e9 + 7;
const double eps = 1e-10;
const int maxn = 70 + 10;
double a[maxn][maxn], x[maxn];

inline int sgn(double x) {
    return (x > eps) - (x < -eps);
}

int gauss(int n, int m) {
    int r = 0, c = 0;
    while (r < n && c < m) {
        int m_r = r;
        for (int i = r + 1; i < n; i++) {
            if (fabs(a[i][c]) > fabs(a[m_r][c])) m_r = i;
        }
        if (m_r != r) {
            for (int j = c; j <= m; j++)
                swap(a[r][j], a[m_r][j]);
        }
        if (!sgn(a[r][c])) {
            a[r][c] = 0;
            ++c;
            continue;
        }
        for (int i = r + 1; i < n; i++) {
            if (a[i][c]) {
                double t = a[i][c] / a[r][c];
                for (int j = c; j < m + 1; j++) a[i][j] -= a[r][j] * t;
            }
        }
        ++r;
        ++c;
    }
    for (int i = r; i < n; i++)
        if (sgn(a[i][m])) return -1;
    for (int i = m - 1; i > -1; i--) {
        double s = a[i][m];
        for (int j = i + 1; j < m; j++)
            s -= a[i][j] * x[j];
        x[i] = s / a[i][i];
    }
    return 0;
}

struct Matrix {
    int sz;
    // int n, m;
    ll a[maxn][maxn];

    Matrix(int sz_ = 0) : sz(sz_) {
        memset(a, 0, sizeof a);
    }

    void pr() {
        printf("*\n");
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                printf("%lld ", a[i][j]);
            }
            printf("\n");
        }
    }

    void tr() {
        for (int i = 0; i < sz; ++i) {
            for (int j = i + 1; j < sz; ++j) {
                swap(a[i][j], a[j][i]);
            }
        }
    }
} res, t1;

Matrix mul(Matrix a, Matrix b) {
    Matrix res(a.sz);
    // if (a.m != b.n) return res;
    for (int i = 0; i < res.sz; i++) // a.n
        for (int j = 0; j < res.sz; j++) // b.m
            for (int k = 0; k < res.sz; k++) // a.m, b.n
                (res.a[i][j] += a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}

Matrix qp(ll n) {
    //for(int i = 0; i < cur; i++) res.a[i][i] = 1;
    while (n > 0) {
        if (n & 1) res = mul(res, t1);
        t1 = mul(t1, t1);
        n >>= 1;
    }
    return res;
}

ll A[maxn * 2];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int k;
        ll n;
        double b;
        scanf("%d%lld", &k, &n);
        ll sum = 0;
        for (int i = 0; i < 2 * k; i++) {
            scanf("%lld", &A[i]);
            if (i < k) sum = (sum + A[i]) % mod;
            b = A[i];
//            scanf("%lf", &b);
            for (int j = max(k, i + 1); j < 2 * k; j++) {
                if (j - i > k)
                    break;
                else
                    a[j - k][j - i - 1] = b;
            }
            if (i >= k)
                a[i - k][k] = b;
        }
        gauss(k, k);
        for (int i = 0; i < k; i++) {
            if (x[i] == -0.0) x[i] = 0;
        }
        memset(res.a, 0, sizeof res.a);
        res.sz = k + 1;
        for (int i = 0; i < k; ++i) res.a[0][i] = A[i];
        res.a[0][k] = sum;
//        res.pr();
        t1.sz = k + 1;
        memset(t1.a, 0, sizeof t1.a);
        for (int i = 0; i < k - 1; ++i) {
            t1.a[i + 1][i] = 1;
        }
        for (int i = 0; i < k; ++i) {
            t1.a[k - i - 1][k] = t1.a[k - i - 1][k - 1] = (ll)x[i] % mod;
        }
        t1.a[k][k] = 1;
//        t1.pr();
//        for (int i = k; i < n; ++i) {
//            res = mul(res, t1);
//            res.pr();
//        }
        Matrix gg = qp(n - k);
        printf("%lld\n", gg.a[0][k]);
    }
    return 0;
}
```

bm不知道为什么板子过不了样例就没写

看别人题解写的不知道啥玩意？？题解写了分块矩阵去求和比我复杂度还大个8倍不太行。

