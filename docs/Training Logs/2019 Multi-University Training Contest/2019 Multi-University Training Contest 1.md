#2019 Multi-University Training Contest 1


| Date      | Solved | A    | B    | C    | D    | E    | F    | G    | H    | I    | J    | K    | L    | M    |
| --------- | ------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 2019/7/22 | 6/13   | Ø    | O    | .    | Ø    | O    | .    | .    | .    | Ø    | .    | .    | .    | Ø    |

## A. [Blank](https://cn.vjudge.net/contest/313418#problem/A)

用0123构造一个序列，有m个条件，每个条件描述的是`l`到`r`内恰好有`k`种数，求方案数。

`dp[i][j][k][t]`表示设0123分别出现的最后位置为`i_,j_,k_,t_`，那么将这四个位置从大到小排序后得到`i,j,k,t`，所表示的合法方案数。由于每个地方都要填数，其实`i`必然是当前位置，所以可以滚动数组枚举一维`i`，然后递推式很轻易的推出来，如下：
$$
\begin{cases}
dp[i -1][j][k][t] \to dp[i][j][k][t]\\
dp[i -1][j][k][t] \to dp[i][i-1][j][k]\\
dp[i -1][j][k][t] \to dp[i][i-1][j][t]\\
dp[i -1][j][k][t] \to dp[i][i-1][k][t]\\
\end{cases}
$$
注意要去掉所有不合法的情况，对每个r记录所有的`(l,k)`，然后枚举i到r时，如果
$$
1(当前位必有一种数)+(j\ge l) + (k \ge l) + (t \ge l) \neq k
$$
就把该状态改为0。

然后就注意一下多组清零的细节。

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：A.cpp
*   创 建 者： badcw
*   创建日期： 19-7-23
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 105;
const int mod = 998244353;
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

struct mint {
  int n;
  mint(int n_ = 0) : n(n_) {}
};

mint operator+(mint a, mint b) { return (a.n += b.n) >= mod ? a.n - mod : a.n; }
mint operator-(mint a, mint b) { return (a.n -= b.n) < 0 ? a.n + mod : a.n; }
mint operator*(mint a, mint b) { return 1LL * a.n * b.n % mod; }
mint &operator+=(mint &a, mint b) { return a = a + b; }
mint &operator-=(mint &a, mint b) { return a = a - b; }
mint &operator*=(mint &a, mint b) { return a = a * b; }
ostream &operator<<(ostream &o, mint a) { return o << a.n; }

ll mul2(ll x,ll y,ll p)
{
	ll res=(x*y-(ll)((long double)x/p*y+1.0e-8)*p);
	return res<0?res+p:res;
}

mint dp[2][maxn][maxn][maxn];
int n, m;
vector<pair<int, int> > lim[maxn];

int main(int argc, char* argv[]) {
//    freopen("data.in", "r", stdin);
//    freopen("my.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; ++kase) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i) lim[i].clear();
        for (int i = 1, u, v, w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            lim[v].emplace_back(u, w);
        }
        int now = 0;
        mint res = 0;
        dp[1][0][0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) {
                for (int k = 0; k <= j; ++k) {
                    for (int t = 0; t <= k; ++t) {
                        dp[now][j][k][t] = 0;
                    }
                }
            }
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k <= j; ++k) {
                    for (int t = 0; t <= k; ++t) {
                        dp[now][j][k][t] += dp[!now][j][k][t];
                        dp[now][i - 1][j][k] += dp[!now][j][k][t];
                        dp[now][i - 1][k][t] += dp[!now][j][k][t];
                        dp[now][i - 1][j][t] += dp[!now][j][k][t];
                    }
                }
            }
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k <= j; ++k) {
                    for (int t = 0; t <= k; ++t) {
                        for (auto x : lim[i]) {
                            if (1 + (j >= x.first) + (k >= x.first) + (t >= x.first) != x.second) {
                                dp[now][j][k][t] = 0;
                            }
                        }
                        if (i == n) {
                            res += dp[now][j][k][t];
                        }
                    }
                }
            }
            now = !now;
        }
        printf("%d\n", res.n);
    }
    return 0;
}
```





## B. Operation

对每个点维护一个线性基，插入操作为继承上一个点的线性基并插入当前点的值。

维护每个基底组成的点g[i]，在未知L的情况下使查询LR尽可能大，考虑贪心，使组成线性基的点尽可能靠近当前点。

具体操作为，对于某一位的点g[i]，如果pos>g[i]，则把pos与g[i]交换，使pos成为线性基的基底。

对于每个询问，查询第R个线性基所有pos大于L的基底能组成的最大值。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;

int n;
inline int getpos(int x, int lasans) { return (x ^ lasans) % n + 1; }

struct LinearBasis
{
    int f[30], g[30];

    void ins(int x, int pos)
    {
        for(int i = 29; ~i; i --)
        {
            if((x >> i) & 1)
            {
                if(f[i])
                {
                    if(g[i] <= pos) { x ^= f[i]; f[i] ^= x; swap(g[i], pos); }
                    else x ^= f[i];
                }
                else { f[i] = x; g[i] = pos; break; }
            }
        }
    }

    int query(int l)
    {
        int res = 0;
        for(int i = 29; ~i; i --) if(g[i] >= l) res = max(res, res ^ f[i]);
        return res;
    }
}base[maxn];

int main()
{
    int t, q, op, l, r, x;
    scanf("%d", &t);
    while(t --)
    {
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i ++)
        {
            scanf("%d", &x);
            base[i] = base[i - 1];
            base[i].ins(x, i);
        }
        int ans = 0;
        while(q --)
        {
            scanf("%d", &op);
            if(op == 0)
            {
                scanf("%d%d", &l, &r);
                l = getpos(l, ans), r = getpos(r, ans);
                if(l > r) swap(l, r);
                printf("%d\n", ans = base[r].query(l));
            }
            else
            {
                scanf("%d", &x); n ++;
                base[n] = base[n - 1], base[n].ins(x ^ ans, n);
            }
        }
    }
    return 0;
}
```

## D. Vacation

考虑\(O(n)\)的解法。

对于某一辆车\(x\)，计算它到达距离停车线0点向右距离为\(\sum_{i=1}^x l_i​\)的时间，最大值即为答案。

*为什么*：因为如果某一辆车没有到达这个点，它后面的车肯定被它堵住了，也就导致0车不能到达停车线。所以每辆车都超过了它对应的这个位置的时间就是答案。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
int l[maxn], s[maxn], v[maxn];

int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i <= n; i ++) scanf("%d", &l[i]);
        for(int i = 0; i <= n; i ++) scanf("%d", &s[i]);
        for(int i = 0; i <= n; i ++) scanf("%d", &v[i]);
        long long L = 0;
        double ans = 1.0 * s[0] / v[0], tm;
        for(int i = 1; i <= n; i ++)
        {
            L += l[i];
            tm = 1.0 * (L + s[i]) / v[i];
            ans = max(ans, tm);
        }
        printf("%f\n", ans);
    }
    return 0;
}
```

## E. Path

跑出最短路，取能够组成最短路的所有边，建新图求最小割。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 10000 + 10;
const int INF = 0x3f3f3f3f;

//用于表示边的结构体（终点，流量，反向边）
struct edges{int to, cap, rev; };

struct Dinic
{
	vector<edges> G[maxn];	//图的邻接表表示
	int level[maxn];	//顶点到源点的距离标号
	int iter[maxn];	//当前弧

	void init()
	{
	    for(int i = 1; i < maxn; i ++) G[i].clear();
	}
	
	void add(int from, int to, int cap)
	{
		G[from].push_back((edges){to, cap, G[to].size()});
		G[to].push_back((edges){from, 0, G[from].size() - 1});
	}

	//计算从源点出发的距离标号
	void bfs(int s)
	{
		memset(level, -1, sizeof(level));
		queue<int> que;
		level[s] = 0;
		que.push(s);
		while(!que.empty())
		{
			int v = que.front(); que.pop();
			for(int i = 0; i < G[v].size(); i++)
			{
				edges &e = G[v][i];
				if(e.cap > 0 && level[e.to] < 0)
				{
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	//通过DFS寻找增广路
	int dfs(int v, int t, int f)
	{
		if(v == t) return f;
		for(int &i = iter[v]; i<G[v].size(); i++)
		{
			edges &e = G[v][i];
			if(e.cap > 0 && level[v] < level[e.to])
			{
				int d = dfs(e.to, t, min(f, e.cap));
				if(d > 0)
				{
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	//求解从s到t的最大流
	int max_flow(int s, int t)
	{
		int flow = 0;
		for(;;)
		{
			bfs(s);
			if(level[t] < 0) return flow;
			memset(iter, 0, sizeof(iter));
			int f;
			while((f = dfs(s,t,INF)) > 0) flow += f;
		}
	}
}dinic;

struct Edge { int nex, to, tot, w; }edge[maxn];

struct Dijkstra
{
    int head[maxn], dis[maxn], cnt;

    void init()
    {
        memset(head, 0xff, sizeof head);
        cnt = 0;
    }

    void add(int u, int v, int w)
    {
        if(u == v) return;
        int p = -1;
        for(int i = head[u]; ~i; i = edge[i].nex) if(edge[i].to == v) { p = i; break; }
        if(~p)
        {
            if(w < edge[p].w) edge[p].w = w, edge[p].tot = 1;
            else if(w == edge[p].w) edge[p].tot ++;
            return;
        }
        edge[++cnt].nex = head[u];
        edge[cnt].w = w;
        edge[cnt].to = v;
        edge[cnt].tot = 1;
        head[u] = cnt;
    }

    void dijkstra(int s)
    {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
        memset(dis, 0x3f, sizeof dis);
        que.push({0, s}); dis[s] = 0;
        while(!que.empty())
        {
            auto f = que.top(); que.pop();
            int u = f.second, d = f.first;
            if(d != dis[u]) continue;
            for(int i = head[u]; ~i; i = edge[i].nex)
            {
                int v = edge[i].to, w = edge[i].w;
                if(dis[u] + w < dis[v])
                {
                    dis[v] = dis[u] + w;
                    que.push({dis[v], v});
                    dinic.add(u, v, w * edge[i].tot);
                }
                else if(dis[u] + w == dis[v]) dinic.add(u, v, w * edge[i].tot);
            }
        }
    }
}G;

signed main()
{
    int t, n, m, u, v, w;
    scanf("%lld", &t);
    while(t --)
    {
        scanf("%lld%lld", &n, &m);
        G.init();
        dinic.init();
        while(m --)
        {
            scanf("%lld%lld%lld", &u, &v, &w);
            G.add(u, v, w);
        }
        G.dijkstra(1);
        printf("%lld\n", dinic.max_flow(1, n));
    }
    return 0;
}
```

## F. Typewriter

令`dp[i]`表示打出前i个字符的花费。对于第一种操作，`dp[i]=dp[i-1]+p`，对于第二种操作，考虑有一个最小的\(j\)，使\(s(j+1,i)\)是\(s(1,j)\)的子串，此时花费为`dp[i]=dp[j]+q`，有状态转移方程$$dp[i]=min(dp[i-1]+p,dp[j]+q)$$

对第二种情况，考虑用后缀自动机维护串\(s(1,j)\)，当SAM内不存在\(s(j+1,i)\)时不断往后添加字符并使`j=j+1`，直到找到串\(s(j+1,i)\)，复杂度\(O(n)\)。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int maxn = 2e5 + 10;
char s[maxn];
ll p, q, dp[maxn];

struct SuffixAutomation
{
	int last, cnt;
	int ch[maxn << 1][26], fa[maxn << 1], len[maxn << 1];

	void init()
	{
	    last = cnt = 1;
	    memset(ch[1], 0, sizeof ch[1]);
	    fa[1] = len[1] = 0;
    }

    int inline newnode()
    {
        ++cnt;
        memset(ch[cnt], 0, sizeof ch[cnt]);
        fa[cnt] = len[cnt] = 0;
        return cnt;
    }

	void ins(int c)
	{
		int p = last , np = newnode();
		last = np, len[np] = len[p] + 1;
		for(; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
		if(!p) fa[np] = 1;
		else
		{
			int q = ch[p][c];
			if(len[p] + 1 == len[q]) fa[np] = q;
			else
			{
				int nq = newnode();
				len[nq] = len[p] + 1;
				memcpy(ch[nq], ch[q], sizeof ch[q]);
				fa[nq] = fa[q], fa[q] = fa[np] = nq;
				for(; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
			}
		}
	}

	ll solve()
	{
	    int n = strlen(s);
	    init();
	    ins(s[0] - 'a');
	    dp[0] = p;
	    int pos = 1, j = 0;
	    for(int i = 1; i < n; i ++)
        {
            dp[i] = dp[i - 1] + p;
            for(;;)
            {
                while(pos != 1 && len[fa[pos]] >= i - j - 1) pos = fa[pos];
                if(ch[pos][s[i] - 'a'])
                {
                    pos = ch[pos][s[i] - 'a'];
                    break;
                }
                else ins(s[++ j] - 'a');
            }
            dp[i] = min(dp[i], dp[j] + q);
        }
        return dp[n - 1];
	}
}sam;


int main()
{
    while(scanf("%s", s) != EOF)
    {
        scanf("%lld%lld", &p, &q);
        printf("%lld\n", sam.solve());
    }
    return 0;
}
```

## I. String

逐位构造答案，贪心地加入能够加入的字典序最小的字符（判断加入之后剩下的后缀中每种字符的数目是否满足条件）。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

char s[maxn], s1[maxn];
int cnt[maxn][26], l[26], r[26], used[26];
vector<int> g[26];

int main()
{
    int n, m;
    while(scanf("%s%d", s, &m) != EOF)
    {
        n = strlen(s);
        for(int i = 0; i < 26; i ++) scanf("%d%d", &l[i], &r[i]);
        memset(used, 0, sizeof used);
        memset(cnt, 0, sizeof cnt);
        for(int i = 0; i < 26; i ++) g[i].clear();
        for(int i = 0; i < n; i ++) g[s[i] - 'a'].push_back(i);
        for(int i = n - 1; i >= 0; i --)
            for(int j = 0; j < 26; j ++)
                cnt[i][j] = cnt[i + 1][j] + (s[i] == 'a' + j);
        vector<int>::iterator head[26];
        for(int i = 0; i < 26; i ++) head[i] = g[i].begin();

        int last = -1, now = 0;
        for(int i = 0; i < m; i ++)
        {
            for(int j = 0; j < 26; j ++)
            {
                if(used[j] == r[j]) continue;
                while(head[j] != g[j].end() && (*head[j]) <= last) head[j] ++;
                if(head[j] == g[j].end()) continue;

                bool flag = true;
                int sum = 0, pos = *head[j];
                used[j] ++;
                for(int k = 0; k < 26; k ++)
                {
                    if(cnt[pos + 1][k] + used[k] < l[k]) flag = false;
                    sum += max(l[k] - used[k], 0);
                }
                if(sum > m - i - 1) flag = false;
                sum = 0;
                for(int k = 0; k < 26; k ++)
                    sum += min(cnt[pos + 1][k], r[k] - used[k]);
                if(sum < m - i - 1) flag = false;

                if(!flag) used[j] --;
                else
                {
                    s1[i] = 'a' + j;
                    last = pos;
                    now ++;
                    break;
                }
            }
            if(now == i) break;
        }
        s1[m] = 0;
        if(now < m) printf("-1\n");
        else printf("%s\n", s1);
    }
    return 0;
}
```



## M. [Code](https://cn.vjudge.net/problem/HDU-6590)

题意：给n个点，求感知机是否有解（即能否二分类，用一条直线将两种点分开）

题解：分别求两类的凸包，判是否凸包相交，方法是枚举凸包内的每个点看是否在另个凸包内，如果存在这样的点两凸包就相交。

代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;
const int maxn = 1e6 + 5;
#define mp make_pair
#define fi first
#define se second
#define pb push_back
typedef double db;
const db eps=1e-6;
const db pi=acos(-1);
int sign(db k){
    if (k>eps) return 1; else if (k<-eps) return -1; return 0;
}
int cmp(db k1,db k2){return sign(k1-k2);}
int inmid(db k1,db k2,db k3){return sign(k1-k3)*sign(k2-k3)<=0;}// k3 在 [k1,k2] 内

struct point{
    db x,y;
    point operator + (const point &k1) const{return (point){k1.x+x,k1.y+y};}
    point operator - (const point &k1) const{return (point){x-k1.x,y-k1.y};}
    point operator * (db k1) const{return (point){x*k1,y*k1};}
    point operator / (db k1) const{return (point){x/k1,y/k1};}
    int operator == (const point &k1) const{return cmp(x,k1.x)==0&&cmp(y,k1.y)==0;}
    // 逆时针旋转
    point turn(db k1){return (point){x*cos(k1)-y*sin(k1),x*sin(k1)+y*cos(k1)};}
    point turn90(){return (point){-y,x};}
    bool operator < (const point k1) const{
        int a=cmp(x,k1.x);
        if (a==-1) return 1; else if (a==1) return 0; else return cmp(y,k1.y)==-1;
    }
    db abs(){return sqrt(x*x+y*y);}
    db abs2(){return x*x+y*y;}
    db dis(point k1){return ((*this)-k1).abs();}
    point unit(){db w=abs(); return (point){x/w,y/w};}
    void scan(){double k1,k2; scanf("%lf%lf",&k1,&k2); x=k1; y=k2;}
    void print(){printf("%.11lf %.11lf\n",x,y);}
    db getw(){return atan2(y,x);}
    point getdel(){if (sign(x)==-1||(sign(x)==0&&sign(y)==-1)) return (*this)*(-1); else return (*this);}
    int getP() const{return sign(y)==1||(sign(y)==0&&sign(x)==-1);}
};
int inmid(point k1,point k2,point k3){return inmid(k1.x,k2.x,k3.x)&&inmid(k1.y,k2.y,k3.y);}
db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
int onS(point k1,point k2,point q){return inmid(k1,k2,q)&&sign(cross(k1-q,k2-k1))==0;}
vector<point> ConvexHull(vector<point>A,int flag=1){ // flag=0 不严格 flag=1 严格
    int n=A.size(); vector<point>ans(n*2);
    sort(A.begin(),A.end()); int now=-1;
    for (int i=0;i<A.size();i++){
        while (now>0&&sign(cross(ans[now]-ans[now-1],A[i]-ans[now-1]))<flag) now--;
        ans[++now]=A[i];
    } int pre=now;
    for (int i=n-2;i>=0;i--){
        while (now>pre&&sign(cross(ans[now]-ans[now-1],A[i]-ans[now-1]))<flag) now--;
        ans[++now]=A[i];
    } ans.resize(now); return ans;
}
//快速判断点是否在凸包内
int contain(vector<point>A,point q){ // 2 内部 1 边界 0 外部
    int pd=0; A.push_back(A[0]);
    for (int i=1;i<A.size();i++){
        point u=A[i-1],v=A[i];
        if (onS(u,v,q)) return 1; if (cmp(u.y,v.y)>0) swap(u,v);
        if (cmp(u.y,q.y)>=0||cmp(v.y,q.y)<0) continue;
        if (sign(cross(u-v,q-v))<0) pd^=1;
    }
    return pd<<1;
}
int main()
{
    int n, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int op;
        vector<point> t1, t2;
        point x;
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &x.x, &x.y);
            scanf("%d", &op);
            if (op == 1) t1.push_back(x);
            else t2.push_back(x);
        }
        t1 = ConvexHull(t1);
        t2 = ConvexHull(t2);
        int flag = 1;
        for (auto i : t1) {
            if (contain(t2, i)) {
                flag = 0;
                break;
            }
        }
        for (auto j : t2) {
            if (contain(t1, j)) {
                flag = 0;
                break;
            }
        }
        printf("%s\n", flag ? "Successful!" : "Infinite loop!");
    }
    return 0;
}
```

