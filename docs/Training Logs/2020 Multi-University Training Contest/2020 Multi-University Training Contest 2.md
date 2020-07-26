| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |   L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 2](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+2&source=1&searchmode=source) | 2020/7/23 | 5/12   |  O   |  .   |  .   |  .   |  O   |  O   |  .   |  .   |  .   |  O   |  .   |  O  |


## A. Total Eclipse

给一张图，有点权，每次取一个最大的生成子图将这些点的权-1，如果减到0就不能选他了，然后求最少步数，是一个假题原先并没有说要取最大的点数。

可以逆着做并查集，最大权的肯定是用更多的次数，为根节点，然后不断连边即可。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>

	using namespace std;
	typedef long long ll;

	const int maxn = 1e5 + 10;

	vector<int> edge[maxn];
	int b[maxn], c[maxn];
	bool vis[maxn];

	bool cmp(int i, int j) { return b[i] > b[j]; }
	int pre[maxn];

	int Find(int x) { return x == pre[x] ? x : pre[x] = Find(pre[x]); }

	int main()
	{
	    int t;
	    scanf("%d", &t);
	    while(t --)
	    {
	        int n, m;
	        scanf("%d%d", &n, &m);
	        for(int i = 1; i <= n; i ++) scanf("%d", &b[i]);
	        for(int i = 1; i <= n; i ++) edge[i].clear();
	        for(int i = 1; i <= n; i ++) vis[i] = false;
	        for(int i = 1; i <= n; i ++) pre[i] = i;
	        for(int i = 1; i <= m; i ++)
	        {
	            int u, v;
	            scanf("%d%d", &u, &v);
	            edge[u].push_back(v);
	            edge[v].push_back(u);
	        }
	        int tot = 0;
	        for(int i = 1; i <= n; i ++) c[i] = i;
	        c[n + 1] = 0;
	        sort(c + 1, c + n + 1, cmp);
	        ll res = 0;
	        for(int i = 1; i <= n; i ++)
	        {
	            int u = c[i];
	            int root = -1;
	            for(auto v : edge[u])
	            {
	                int fv = Find(v);
	                if(vis[fv]) 
	                {
	                    if(root == -1) root = fv;
	                    else 
	                    {
	                        if(root != fv)
	                        {
	                            pre[fv] = root;
	                            tot --;
	                        }
	                    }
	                }
	            }
	            vis[u] = true;
	            if(root == -1) 
	            {
	                tot ++;
	            }
	            if(root != -1) pre[u] = root;

	            int now = b[c[i]] - b[c[i + 1]];
	            res += 1ll * now * tot;
	        }
	        printf("%lld\n", res);
	    }
	    return 0;
	}
	```

## E. New Equipments

n 个人，每个人有a，b，c属性，有无限个装备，求其中k个人拿一种装备j，获得的最小 $\sum a_i*j^2+b_i*j+c_i$。要求 k=1~n 的所有答案。

直接预处理每个人对称轴左右 50 个点，一共点数 50*50+50=2550，在二分图上跑最小费用流即可，对于答案增加将残余网络增广即可。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>

	using namespace std;
	typedef long long ll;

	const int maxn = 10000 + 10;
	const int inf = 0x3f3f3f3f;
	const ll INF = 0x3f3f3f3f3f3f3f3fll;

	struct Edge { int from, to, cap, flow; ll cost; };

	struct MCMF
	{
	    int n, m;
	    vector<Edge> edges;
	    vector<int> G[maxn];
	    bool inq[maxn];
	    int path[maxn], a[maxn];
	    ll dis[maxn];

	    void init(int n) {
	        this->n = n;
	        for(int i = 0;i <= n;i ++)
	            G[i].clear();
	        edges.clear();
	    }

	    void add(int from, int to, int cap, ll cost)
	    {
	        edges.push_back(Edge{from, to, cap, 0, cost});
	        edges.push_back(Edge{to, from, 0, 0, -cost});
	        m = edges.size();
	        G[from].push_back(m - 2);
	        G[to].push_back(m - 1);
	    }

	    bool Bellman_Ford(int s, int t, int& flow, ll& cost)
	    {
	        for(int i = 0; i <= n; i++) dis[i] = INF;
	        memset(inq, 0, sizeof inq);
	        dis[s]=0, inq[s]=true, path[s]=0, a[s]=inf;
	        queue<int> Q;
	        Q.push(s);
	        while(!Q.empty())
	        {
	            int u = Q.front(); Q.pop();
	            inq[u] = false;
	            for(int i = 0; i < G[u].size(); i++)
	            {
	                Edge& e = edges[G[u][i]];
	                if(e.cap > e.flow && dis[e.to] > dis[u] + e.cost)
	                {
	                    dis[e.to] = dis[u] + e.cost;
	                    path[e.to] = G[u][i];
	                    a[e.to] = min(a[u], e.cap - e.flow);
	                    if(!inq[e.to])
	                    {
	                        Q.push(e.to);
	                        inq[e.to] = true;
	                    }
	                }
	            }
	        }
	        if(dis[t] == INF) return false;     //求最小费用最大流
	        //if(1ll * dis[t] * a[t] > 0) return false; 求可行流最小费用，因此当费用增量大于0时不继续增加流量
	        flow += a[t];
	        cost += dis[t] * a[t];
	        for(int u = t; u != s; u = edges[path[u]].from)
	        {
	            edges[path[u]].flow += a[t];
	            edges[path[u] ^ 1].flow -= a[t];
	        }
	        return true;
	    }

	    ll mincostMaxFlow(int s, int t)
	    {
	        int flow = 0; ll cost = 0;
	        while(Bellman_Ford(s, t, flow, cost));
	        return cost;
	    }
	}ans;


	ll a[55], b[55], c[55];
	int n, m, tot;
	map<int, int> mp;

	ll cal(int x, int p)
	{
	    return a[x] * p * p + b[x] * p + c[x];
	}

	void addEdge(int x)
	{
	    ll p = -b[x] / (2 * a[x]);
	    int cnt = 0;
	    if(p < 0) p = 0;
	    if(p > m) p = m;
	    int l = p, r = p + 1;
	    while(cnt <= 50)
	    {
	        if(l < 1 && r > m) break;
	        if(l >= 1)
	        {
	            if(mp.count(l) == 0) mp[l] = tot ++;
	            int v = mp[l];
	            ll val = cal(x, l);
	            ans.add(x, v, 1, val);
	            l --;
	            cnt ++;
	        }
	        if(r <= m)
	        {
	            if(mp.count(r) == 0) mp[r] = tot ++;
	            int v = mp[r];
	            ll val = cal(x, r);
	            ans.add(x, v, 1, val);
	            r ++;
	            cnt ++;
	        }
	    }
	}

	int main()
	{
	    int t;
	    scanf("%d", &t);
	    while(t --)
	    {
	        scanf("%d%d", &n, &m);
	        for(int i = 1; i <= n; i ++) scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	        mp.clear();
	        int SS = 0, T = 4001, S = T + 1;
	        ans.init(S);
	        tot = n + 1;
	        for(int i = 1; i <= n; i ++) addEdge(i);
	        for(int i = 1; i <= n; i ++) ans.add(SS, i, 1, 0);
	        for(int i = n + 1; i < tot; i ++) ans.add(i, T, 1, 0);
	        ll res = 0;
	        for(int k = 1; k <= n; k ++)
	        {
	            ans.add(S, SS, 1, 0);
	            res += ans.mincostMaxFlow(S, T);
	            printf("%lld%c", res, " \n"[k == n]);
	        }
	    }

	    return 0;
	}
	```

## F. The Oculus

fib[1] = 1, fib[2] = 2, fib[i] = fib[i - 1] + fib[i - 2]

已知一个数字用 fib 和从高到低贪心和表示是唯一的。

给 A B 两个数字用 fib 的表示方案，给出 $C=A*B$ 用 fib 表示方案的错误方案（是正确方案中把一个1变为0），求改的是哪个位置。

直接 hash，由于乘法和加法对取模都是天然成立的。

考虑将 $fib_i$ 的 hash 值处理出来，试填每一位合法的 C 为 0 的点即可。赛中使用双 hash 通过，实际自然溢出都可以。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/23 14:13
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 1e7+50;
	const int mod = 1e9+7;
	const int mod2 = 998244353;
	ll qp(ll a, ll n, ll mod = ::mod) {
	    ll res = 1;
	    while (n > 0) {
	        if (n & 1) res = res * a % mod;
	        a = a * a % mod;
	        n >>= 1;
	    }
	    return res;
	}

	template<class T> void _R(T &x) { cin >> x; }
	void _R(int &x) { scanf("%d", &x); }
	void _R(int64_t &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const int64_t &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	ll f[maxn] = {1, 1, 2};
	ll g[maxn] = {1, 1, 2};
	int vis[maxn];

	int main(int argc, char* argv[]) {
	    for (int i = 3; i <= 1e7+1; ++i) {
	        f[i] = (f[i - 2] + f[i - 1]) % mod;
	        g[i] = (g[i - 2] + g[i - 1]) % mod2;
	    }
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        int n1, n2, n3;
	        R(n1);
	        ll m1 = 0, m2 = 0, m3 = 0;
	        ll g1 = 0, g2 = 0, g3 = 0;
	        for (int i = 1; i <= n1; ++i) {
	            int x;
	            R(x);
	            if (x == 1) {
	                m1 = (m1 + f[i]) % mod;
	                g1 = (g1 + g[i]) % mod2;
	            }
	        }
	        R(n2);
	        for (int i = 1; i <= n2; ++i) {
	            int x;
	            R(x);
	            if (x == 1) {
	                m2 = (m2 + f[i]) % mod;
	                g2 = (g2 + g[i]) % mod2;
	            }
	        }
	        ll mc = m1 * m2 % mod;
	        ll gc = g1 * g2 % mod2;
	        R(n3);
	        for (int i = 1; i <= n3; ++i) {
	            R(vis[i]);
	            if (vis[i] == 1) {
	                m3 = (m3 + f[i]) % mod;
	                g3 = (g3 + g[i]) % mod2;
	            }
	        }
	        vis[0] = 0;
	        vis[n3 + 1] = 0;
	        int flag = 0;
	        for (int i = 1; i <= n3; ++i) {
	            if (!vis[i - 1] && !vis[i + 1] && !vis[i]) {
	                m3 = (m3 + f[i]) % mod;
	                g3 = (g3 + g[i]) % mod2;
	                if ((mc - m3) % mod == 0 && (gc - g3) % mod2 == 0) {
	                    flag = i;
	                    break;
	                }
	                m3 = (m3 - f[i]) % mod;
	                g3 = (g3 - g[i]) % mod2;
	            }
	        }
	        W(flag);
	    }
	    return 0;
	}
	```

## J. Lead of Wisdom

给 50 个物品每个有 abcd 四个权，每个物品有种类，每种只能挑一个。

求最大化 DMG=(100+∑i∈Sai)(100+∑i∈Sbi)(100+∑i∈Sci)(100+∑i∈Sdi)

直接爆搜，把一个物品都没有的种类跳过还有将完全逆序对去掉即可剪枝通过。

需要分析复杂度，最大的情况应该是每种物品 3 个，最后一组 2 个，需要 $3^{16}*2$ 的搜索树。

???note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/23 12:24
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 51;
	const int mod = 1e9+7;
	ll qp(ll a, ll n, ll mod = ::mod) {
	    ll res = 1;
	    while (n > 0) {
	        if (n & 1) res = res * a % mod;
	        a = a * a % mod;
	        n >>= 1;
	    }
	    return res;
	}

	template<class T> void _R(T &x) { cin >> x; }
	void _R(int &x) { scanf("%d", &x); }
	void _R(int64_t &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const int64_t &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	struct node {
	    int a, b, c, d;
	    void set(int x, int y, int z, int k) {
	        a = x, b = y, c = z, d = k;
	    }
	};

	node s[maxn][maxn];
	node pre[maxn];
	node now;
	int sz[maxn];
	int nxt[maxn];
	int n, k;
	ll res = 0;

	inline void cal() { res = max(res, 1ll * (100 + now.a) * (100 + now.b) * (100 + now.c) * (100 + now.d)); }

	inline void dfs(int dep) {
	    if (dep == k) {
	        cal();
	        return;
	    }
	    if (sz[dep] == 0) {
	        dfs(dep + 1);
	    } else {
	        for (int i = 0; i < sz[dep]; ++i) {
	            now.a += s[dep][i].a;
	            now.b += s[dep][i].b;
	            now.c += s[dep][i].c;
	            now.d += s[dep][i].d;
	            if (s[dep][i].a <= 0 && s[dep][i].b <= 0 && s[dep][i].c <= 0 && s[dep][i].d <= 0) continue;
	            dfs(nxt[dep]);
	        }
	        now.a -= pre[dep].a;
	        now.b -= pre[dep].b;
	        now.c -= pre[dep].c;
	        now.d -= pre[dep].d;
	    }
	}

	int main(int argc, char* argv[]) {
	//     freopen("data.in","r",stdin);
	//    freopen("data.out", "w", stdout);
	//    clock_t ST = clock();
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        R(n, k);
	        for (int i = 0; i < k; ++i) sz[i] = 0, pre[i].set(0, 0, 0, 0);
	        int t, a, b, c, d;
	        for (int i = 0; i < n; ++i) {
	            R(t, a, b, c, d);
	            s[t - 1][sz[t - 1] ++] = {a - pre[t - 1].a, b - pre[t - 1].b, c - pre[t - 1].c, d - pre[t - 1].d};
	            pre[t - 1].set(a, b, c, d);
	        }
	        for (int i = 0; i < k; i = nxt[i]) {
	            int j = i + 1;
	            for (; j < k; ++j) {
	                if (sz[j]) break;
	            }
	            nxt[i] = j;
	        }
	        res = 0;
	        now.set(0, 0, 0, 0);
	        dfs(0);
	        W(res);
	    }
	//    cerr << "time: " << ((clock() - ST) * 1000.0 / CLOCKS_PER_SEC) << "ms" << endl;
	    return 0;
	}
	```

## L. String Distance


给一个 1e5 长度的 s 串，一个 20 长度的 t 串，q（ 1e5 ） 次询问 $[l,r]$，问 `s[l...r]` 最少需要改动多少次（在任意位置删除或添加字符）把他变成 t 串。

考虑离线询问，对于询问为 r 的一次性处理完。

考虑答案其实是 $r - l + 1 + t - 2 * lcs(s[l...r], t)$

做 dp， $dp_{i,j,k}$ 表示 s 到了第 i 位，与 t 的前 j 位的 lcs 为 k 离 i 的最近点是哪一位。

转移比较轻松，只要预处理了 $a\to z$ 在 t 中第一次出现的位置 x，比如我现在枚举到 $s[i]$，那么 $dp[i][x\to m][1]$ 都为 i，然后做转移，可以用滚动数组优化。

到了一个 r 的时候，可以从大到小枚举 k，如果有一个 $dp[i][j][k]$ 的值不小于 l 则说明 lcs 为 k。

时间复杂度 $O(n*m*m+q*logq+q*m*m)$，用滚动数组优化空间复杂度为 $O(m*m+m*26)$

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/23 14:58
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 1e5+50;
	const int mod = 1e9+7;
	ll qp(ll a, ll n, ll mod = ::mod) {
	    ll res = 1;
	    while (n > 0) {
	        if (n & 1) res = res * a % mod;
	        a = a * a % mod;
	        n >>= 1;
	    }
	    return res;
	}

	template<class T> void _R(T &x) { cin >> x; }
	void _R(int &x) { scanf("%d", &x); }
	void _R(int64_t &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const int64_t &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	char s[maxn];
	char t[25];
	int n, m;

	struct op {
	    int idx;
	    int l, r;
	    bool operator < (const op& oth) const {
	        return r < oth.r;
	    }
	}p[maxn];

	int dp[25][25], pd[25][25];
	int ans[maxn], fi[26];

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        scanf("%s%s", s + 1, t + 1);
	        n = strlen(s + 1);
	        m = strlen(t + 1);
	        for (int i = 0; i < 26; ++i) fi[i] = -1;
	        for (int i = 1; i <= m; ++i) if (fi[t[i] - 'a'] == -1) fi[t[i] - 'a'] = i;
	        int q;
	        R(q);
	        int l, r;
	        for (int i = 0; i < q; ++i) {
	            R(l, r);
	            p[i] = {i, l, r};
	        }
	        sort(p, p + q);
	        int now = 0;
	        memset(dp, 0, sizeof dp);
	        memset(pd, 0, sizeof pd);
	        for (int i = 1; i <= n; ++i) {
	            if (fi[s[i] - 'a'] != -1) dp[fi[s[i] - 'a']][1] = i;
	            for (int j = 2; j <= m; ++j) {
	                for (int k = 2; k <= m; ++k) {
	                    dp[j][k] = pd[j][k];
	                }
	                if (s[i] == t[j]) {
	                    for (int k = 1; k < m; ++k) {
	                        dp[j][k + 1] = pd[j - 1][k];
	                    }
	                }
	            }
	//            cerr << i << " ** : \n";
	            for (int j = 1; j <= m; ++j) {
	                for (int k = 1; k <= m; ++k) {
	                    if (dp[j][k] < dp[j - 1][k]) dp[j][k] = dp[j - 1][k];
	                    pd[j][k] = dp[j][k];
	//                    cerr << pd[j][k] << " ";
	                }
	//                cerr << endl;
	            }
	            while (now < q && p[now].r == i) {
	                ans[p[now].idx] = p[now].r - p[now].l + 1 + m;
	                for (int j = m; j >= 1; --j) {
	                    if (pd[m][j] >= p[now].l) {
	                        ans[p[now].idx] = p[now].r - p[now].l + 1 + m - j * 2;
	                        break;
	                    }
	                }
	                now ++;
	            }
	        }
	        for (int i = 0; i < q; ++i) W(ans[i]);
	    }
	    return 0;
	}
	```