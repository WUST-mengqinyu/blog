| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |Ø
| [2020 Multi-University Training Contest 4](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+4&source=1&searchmode=source) | 2020/7/30 | 7/12   |  .   |  O   |  .   |  O   |  O   |  .   |  .   |  .   |  .   |  .   |   O   |   .   |


## B. Blow up the Enemy

选择一个武器，轮流打，问一方随机选另一方选最优的获胜概率，直接模拟一下最大 0，1，0.5 取一下平均数。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/30 12:48
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 1e3+50;
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
	void _R(ll &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const ll &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	ll a[maxn], d[maxn];
	ll t[maxn];

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        int n;
	        R(n);
	        ll mn = 1e18;
	        for (int i = 1; i <= n; ++i) {
	            R(a[i], d[i]);
	            ll tim = (100 / a[i] + (100 % a[i] ? 1 : 0));
	            t[i] = d[i] * (tim - 1);
	            mn = min(mn, t[i]);
	        }
	        ll tmp = 0;
	        for (int i = 1; i <= n; ++i) {
	            if (mn == t[i]) {
	                tmp ++;
	            }
	        }
	        W(1 - tmp * 0.5 / n);
	    }
	    return 0;
	}
	```


## C. Contest of Rope Pulling

一堆里面 n 个物品，每个有大小 x 和价值 w，令一堆有 m 个也有这两个属性。

问在一堆中挑选出大小和二堆中完全一样的最大价值和。

$n,m \le 1000~x \le 1000~-1e9\le w \le 1e9$

显然是一个背包性质的问题不可能存在线性或者优化的做法。将 m 个物品的大小弄成负数加到 n 堆里去，然后最后就是容量为 0 的最大值，随机物品顺序之后确定一个阈值 k，考虑到全 1000 导致值域达到 1e6 级别的概率太小。

阈值取到 80000 就可以通过此题。

复杂度 $O((n+m)*k)$

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/31 12:31
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 1e3+50;
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
	void _R(ll &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const ll &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	int n, m;

	struct node {
	    int w, v;
	    int flag;
	};

	const int lim = 80000;
	ll dp[lim * 2 + 5];
	//map<int, ll> dp;

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        R(n, m);
	        vector<node> a(n + m);
	        for (int i = 0; i < n; ++i) R(a[i].w, a[i].v), a[i].flag = 1;
	        for (int i = 0; i < m; ++i) R(a[i + n].w, a[i + n].v), a[i + n].flag = -1;
	        n += m;
	        int tt = 1;
	        ll res = 0;
	        while (tt--) {
	            random_shuffle(a.begin(), a.end());
	//            for (auto i : a) {
	//                cerr << i.v << " " << i.w << " " << i.flag << endl;
	//            }
	//            cerr << "*\n";
	//            dp.clear();
	            for (int i = -lim; i <= lim; ++i) dp[i + lim] = -1e18;
	            dp[lim] = 0;
	            for (int i = 0; i < n; ++i) {
	                if (a[i].flag > 0) {
	                    for (int j = lim; j >= -lim + a[i].w; --j) {
	                        if (dp[j - a[i].w + lim] != -1e18) dp[j + lim] = max(dp[j + lim], dp[j - a[i].w + lim] + a[i].v);
	                    }
	                } else {
	                    for (int j = -lim; j <= lim - a[i].w; ++j) {
	                        if (dp[j + a[i].w + lim] != -1e18) dp[j + lim] = max(dp[j + lim], dp[j + a[i].w + lim] + a[i].v);
	                    }
	                }
	            }
	            res = max(res, dp[lim]);
	        }
	        W(res);
	    }
	    return 0;
	}
	```

## D. Deliver the Cake

一张图，求 1~n 的最短路，每个点有左右手限制，如果在当前位置是左手，下一个节点是右手限制需要额外 x 的时间。有的点没有限制。

对限制左右手的点当作一个点看，而不限制的拆为用左手和用右手两个点相连权为 x，然后建图跑最短路即可。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/8/8 0:05
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 2e5+50;
	const int mod = 1e9+7;
	ll qp(ll a, ll n, int mod = ::mod) {
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
	void _R(ll &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const ll &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	int n, m, x, tot;
	char S[maxn];
	int pos[2][maxn];

	vector<pair<int, ll> > edge[maxn];
	ll dist[maxn];
	const ll inf = 0x3f3f3f3f3f3f3f3f;

	ll dij(int s, int t) {
	    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > qu;
	    for (int i = 0; i <= tot; ++i) dist[i] = inf;
	    dist[s] = 0;
	    qu.push({0, s});
	    while (!qu.empty()) {
	        auto f = qu.top(); qu.pop();
	        int u = f.second; ll d = f.first;
	        if (d != dist[u]) continue;
	        for (auto it : edge[u]) {
	            int v = it.first, w = it.second;
	            if (dist[u] + w < dist[v]) {
	                dist[v] = dist[u] + w;
	                qu.push({dist[v], v});
	            }
	        }
	    }
	    return min(dist[pos[0][t]], dist[pos[1][t]]);
	}

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        int s, t;
	        R(n, m, s, t, x);
	        scanf("%s", S + 1);
	        tot = 0;
	        for (int i = 1; i <= n; ++i) {
	            if (S[i] == 'L') pos[0][i] = ++tot, pos[1][i] = 0;
	            else if (S[i] == 'R') pos[1][i] = ++tot, pos[0][i] = 0;
	            else pos[0][i] = ++tot, pos[1][i] = ++tot;
	        }
	        for (int i = 1; i <= tot + 1; ++i) edge[i].clear();
	        for (int i = 1; i <= m; ++i) {
	            int u, v, w;
	            R(u, v, w);
	            for (int j = 0; j < 2; ++j) {
	                if (pos[j][u] == 0) continue;
	                for (int k = 0; k < 2; ++k) {
	                    if (pos[k][v] == 0) continue;
	                    edge[pos[j][u]].emplace_back(pos[k][v], w + x * (j != k));
	                    edge[pos[k][v]].emplace_back(pos[j][u], w + x * (j != k));
	//                    cerr << pos[j][u] << " " << pos[k][v] << " " << w + x * (j != k) << endl;
	                }
	            }
	        }
	        int Sx = ++tot;
	        if (pos[0][s]) edge[Sx].emplace_back(pos[0][s], 0);
	        if (pos[1][s]) edge[Sx].emplace_back(pos[1][s], 0);
	        W(dij(Sx, t));
	    }
	    return 0;
	}
	```

## E. Equal Sentences

给一个句子，求将他中的每个单词最多移动 1 的位置的本质不同串个数。

显然 dp 就完事了，$dp_{i,0/1}$ 表示第 i 个位置是否移动的方案数。遇到相同单词只能转移 0 的方案数即可。

??? note "Code“
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/30 12:58
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
	void _R(ll &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const ll &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	int n;
	string s[maxn];
	ll dp[maxn][2];

	int main(int argc, char* argv[]) {
	    ios::sync_with_stdio(0);
	    cin.tie(0);
	    int T;
	    cin >> T;
	    for (int kase = 1; kase <= T; ++kase) {
	        cin >> n;
	        for (int i = 1; i <= n; ++i) cin >> s[i];
	        dp[1][0] = 1;
	        dp[1][1] = 0;
	        for (int i = 2; i <= n; ++i) {
	            dp[i][0] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
	            dp[i][1] = dp[i - 1][0] * (s[i] != s[i - 1]);
	        }
	        cout << (dp[n][0] + dp[n][1]) % mod << '\n';
	    }
	    return 0;
	}
	```

## G. Go Running

有若干个速度为 1 在数轴上移动的点，它可能出现或者消失在任何时候，给一些出现事件对 $(t,x)$ 表示 t 时刻在 x 点有点。求最少有多少个不同的点。

显然的一点是如果考虑全部是往右的点，$t-x$ 相等的点是可以合并的，往左则是 $t+x$ 相等可以合并。

那么问题转换为在二维坐标上，取多少个斜率为 1 或 -1 的直线能把全部点覆盖。

考虑对一个点 $t-x$ $t+x$ 建二分图连边（注意就算某个 $t-x$ 若与某个 $t+x$ 相同它们也是两个不同点），问题转换为最小点覆盖即可用 Dinic 或者 Hopcroft二分图匹配算法 以 $O(n\sqrt(m))$ 复杂度通过。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/8/8 0:41
	*
	================================================================*/
	#include <bits/stdc++.h>
	#define VI vector<int>
	#define ll long long
	using namespace std;
	const int maxn = 1e5+50;
	const int mod = 1e9+7;
	ll qp(ll a, ll n, int mod = ::mod) {
	    ll res = 1;
	    while (n > 0) {
	        if (n & 1) res = res * a % mod;
	        a = a * a % mod;
	        n >>= 1;
	    }
	    return res;
	}
	namespace IO {
	    template<class T>
	    void _R(T &x) { cin >> x; }
	    void _R(int &x) { scanf("%d", &x); }
	    void _R(ll &x) { scanf("%lld", &x); }
	    void _R(double &x) { scanf("%lf", &x); }
	    void _R(char &x) { x = getchar(); }
	    void _R(char *x) { scanf("%s", x); }
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
	    void _W(const pair<T, U> &x) {_W(x.F),putchar(' '),_W(x.S);}
	    template<class T>
	    void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	    void W() {}
	    template<class T, class... U>
	    void W(const T &head, const U &... tail) {_W(head),putchar(sizeof...(tail) ? ' ' : '\n'),W(tail...);}
	}
	using namespace IO;
	//复杂度O(n^0.5*m)
	struct Hopcroft {
	#define maxn 100005
	#define maxm 100005
	#define INF 0x3f3f3f3f
	    struct Edge { int v, next; } edge[maxm];
	    int nx, cnt, dis;
	    int first[maxn];
	    int xlink[maxn], ylink[maxn];
	    int dx[maxn], dy[maxn];
	    int vis[maxn];
	    void init(int n) {
	        cnt = 0;
	        for (int i = 0; i <= n; ++i) first[i] = ylink[i] = xlink[i] = -1;
	        nx = n + 1;
	    }
	    void add_edge(int u, int v) {
	        edge[cnt].v = v, edge[cnt].next = first[u], first[u] = cnt++;
	    }
	    int bfs() {
	        queue<int> q;
	        dis = INF;
	        for (int i = 0; i < nx; ++i) dx[i] = dy[i] = -1;
	        for (int i = 0; i < nx; i++) {
	            if (xlink[i] == -1) {
	                q.push(i);
	                dx[i] = 0;
	            }
	        }
	        while (!q.empty()) {
	            int u = q.front();
	            q.pop();
	            if (dx[u] > dis) break;
	            for (int e = first[u]; e != -1; e = edge[e].next) {
	                int v = edge[e].v;
	                if (dy[v] == -1) {
	                    dy[v] = dx[u] + 1;
	                    if (ylink[v] == -1) dis = dy[v];
	                    else {
	                        dx[ylink[v]] = dy[v] + 1;
	                        q.push(ylink[v]);
	                    }
	                }
	            }
	        }
	        return dis != INF;
	    }
	    int find(int u) {
	        for (int e = first[u]; e != -1; e = edge[e].next) {
	            int v = edge[e].v;
	            if (!vis[v] && dy[v] == dx[u] + 1) {
	                vis[v] = 1;
	                if (ylink[v] != -1 && dy[v] == dis) continue;
	                if (ylink[v] == -1 || find(ylink[v])) {
	                    xlink[u] = v, ylink[v] = u;
	                    return 1;
	                }
	            }
	        }
	        return 0;
	    }
	    int MaxMatch() {
	        int ans = 0;
	        for (int i = 0; i < nx; ++i) vis[i] = 0;
	        while (bfs()) {
	            for (int i = 0; i < nx; ++i) vis[i] = 0;
	            for (int i = 0; i < nx; i++)
	                if (xlink[i] == -1)
	                    ans += find(i);
	        }
	        return ans;
	    }
	#undef maxn
	#undef maxm
	} solve;
	int t[maxn], x[maxn], n;
	vector<int> xpos, ypos;
	int main(int argc, char *argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        R(n);
	        xpos.clear(), ypos.clear();
	        for (int i = 1; i <= n; ++i) {
	            R(t[i], x[i]);
	            xpos.push_back(t[i] + x[i]);
	            ypos.push_back(t[i] - x[i]);
	        }
	        sort(xpos.begin(), xpos.end());
	        sort(ypos.begin(), ypos.end());
	        xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
	        ypos.erase(unique(ypos.begin(), ypos.end()), ypos.end());
	        solve.init(max(xpos.size(), ypos.size()));
	        for (int i = 1; i <= n; ++i) {
	            int pos = lower_bound(xpos.begin(), xpos.end(), t[i] + x[i]) - xpos.begin();
	            int pos2 = lower_bound(ypos.begin(), ypos.end(), t[i] - x[i]) - ypos.begin();
	            solve.add_edge(pos, pos2);
	        }
	        W(solve.MaxMatch());
	    }
	    return 0;
	}
	```

## K. Kindergarten Physics

求天体 t 时间内运动距离，发现不会超过 spj 的最小值直接输出原答案即可。

## L. Last Problem

二维点填数构造，如果要在一个点填 x 需要它的上下左右四个方向存在 x-4~x-1，略过 x-4~x-1 中的非正数。求构造出一个 n 的方案。

```
020      030     050   040  060
314      425     647   536  758
050      060     080   070  090
```

懂得都懂，不懂就不懂

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/31 18:00
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 105;
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
	void _R(ll &x) { scanf("%lld", &x); }
	void _R(double &x) { scanf("%lf", &x); }
	void _R(char &x) { x = getchar(); }
	void _R(char *x) { scanf("%s", x); }
	void R() {}
	template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
	template<class T> void _W(const T &x) { cout << x; }
	void _W(const int &x) { printf("%d", x); }
	void _W(const ll &x) { printf("%lld", x); }
	void _W(const double &x) { printf("%.16f", x); }
	void _W(const char &x) { putchar(x); }
	void _W(const char *x) { printf("%s", x); }
	template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
	template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
	void W() {}
	template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }

	int n;

	int xc[] = {-1, 0, 0, 1};
	int yc[] = {0, 1, -1, 0};
	map<pair<int, int>, int> mp;

	void deal(int x, int y, int dep) {
	    if (mp[make_pair(x, y)] == dep) return;
	    for (int i = 0; i < 4; ++i) {
	        if (dep - 4 + i <= 0) continue;
	        deal(x + xc[i], y + yc[i], dep - 4 + i);
	    }
	    mp[make_pair(x, y)] = dep;
	    W(x, y, dep);
	}

	int main(int argc, char* argv[]) {
	    R(n);
	    deal(0, 0, n);
	    return 0;
	}
	```