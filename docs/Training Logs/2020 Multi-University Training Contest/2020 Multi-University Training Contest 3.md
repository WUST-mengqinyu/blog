| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 3](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+3&source=1&searchmode=source) | 2020/7/28 | 7/11   |  Ø   |  .  |  Ø   |  O   |  O   |  .   |  Ø   |  O   |  O   |  .   |  .  |

## A. Tokitsukaze, CSL and Palindrome Game

题意：给一个回文串S，Tokitsukaze和CSL每次会选择回文子串$S_{a..b}$和$S_{c..d}$。有一个空串P，每次会等概率的在a-z之间选择一个字符，$E(S)$表示S成为P子串的操作次数期望。比较$E(S_{a...b})$和$E(S_{c...d})$的期望大小。

推荐阅读[《浅谈生成函数在掷骰子问题上的应用》](https://github.com/enkerewpo/OI-Public-Library/blob/master/IOI%E4%B8%AD%E5%9B%BD%E5%9B%BD%E5%AE%B6%E5%80%99%E9%80%89%E9%98%9F%E8%AE%BA%E6%96%871999-2019/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf), 并再次推荐阅读[金策-字符串算法选讲](https://www.docin.com/p-1936795644.html)来获取本题相关前置知识

前置知识1：对于串S，如果$S[1,i]=S[n-i+1,n]$(长度为i的前缀等于后缀），则称$S[1,i]$是S的一个border。

$E(S)=\sum_i^{|S|}a_i*m^i$，其中$a_i$代表前缀$S[1,i]$是否是$S$的border

因为后面带了个i的幂次，显然越靠后的前缀贡献越大，所以对于$E(S_{a...b})$和$E(S_{c...d})$，比较一下他们的字典序就好。

前置知识2：回文串的border由是logn级别个等差数列拼接成的，所以对于一个回文串，一直沿着fail树往上跳就可以得到它的所有border。然后根据等差性质，预处理一下border的若干个等差数列，每次对两组等差数列从后往前做比较即可。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>

	using namespace std;
	typedef long long ll;

	const int maxn = 1e5 + 10;
	const int N = 26;

	struct node { int s, d, r; }; 

	struct PAM 
	{
		int n, p, last;
		int nex[maxn][N], fail[maxn], cnt[maxn], num[maxn], len[maxn], S[maxn], pos[maxn];
		int diff[maxn], pre[maxn];

		int newnode(int l) 
		{
			for(int i = 0; i < N; i ++) nex[p][i] = 0;
			cnt[p] = num[p] = 0;
			len[p] = l;
			return p ++;
		}

		void init()
		{
			n = last = p = 0; 
			newnode(0); newnode(-1);
			S[n] = -1;
			fail[0] = 1;
		}

		int get_fail(int x)
		{
			while(S[n - len[x] - 1] != S[n]) x = fail[x];
			return x;
		}

		void add(int c)
		{
			S[++ n] = c;
			int cur = get_fail(last);
			if(!nex[cur][c])
			{
				int now = newnode(len[cur] + 2);
				fail[now] = nex[get_fail(fail[cur])][c];
				nex[cur][c] = now;
				num[now] = num[fail[now]] + 1;
			}
			last = nex[cur][c];
			diff[last] = len[last] - len[fail[last]];
			if(diff[last] != diff[fail[last]] || len[fail[last]] == 0 || len[fail[last]] == -1) pre[last] = last; 
			else pre[last] = pre[fail[last]];
			num[last] ++;
			pos[n] = last;
		}

		vector<node> getBorder(int x, int lim)
		{
			x = pos[x];
			vector<node> ve;
			while(len[x] > 0)
			{
				int y = pre[x];
				if(len[y] <= lim)
				{
					if(len[x] <= lim) ve.push_back({ len[x], diff[x], (len[x] - len[y]) / diff[x] });
					else ve.push_back({ lim, diff[x], (lim - len[y]) / diff[x] });
				}
				x = fail[y];
			}
			ve.push_back({0, 0, 0});
			return ve;
		}
		
		int comp(int a, int b, int c, int d)
		{
			auto A = getBorder(b, b - a + 1); auto B = getBorder(d, d - c + 1);
			int i = 0, j = 0, lenA = A.size(), lenB = B.size();
			while(i < lenA - 1 && j < lenB - 1)
			{
				if(A[i].s != B[j].s) return A[i].s < B[j].s ? -1 : 1;
				if(A[i].d == B[j].d)
				{
					if(A[i].r == B[j].r) i ++, j ++;
					else if(A[i].r > B[j].r) 
					{
						A[i].s -= (B[j].r + 1) * A[i].d;
						A[i].r -= B[j].r + 1;
						j ++;
						if(A[i].r == 0) i ++;
					}
					else 
					{
						B[j].s -= (A[i].r + 1) * B[j].d;
						B[j].r -= A[i].r + 1;
						i ++;
						if(B[j].r == 0) j ++;
					}
				}
				else
				{
					if(A[i].r == 0 && B[j].r == 0) i ++, j ++; 
					else if(A[i].r == 0) return A[i + 1].s < B[j].s - B[j].d ? -1 : 1;  
					else if(B[j].r == 0) return A[i].s - A[i].d < B[j + 1].s ? -1 : 1;
					else return A[i].d > B[j].d ? -1 : 1;
				}
			}
			if(i == lenA - 1 && j == lenB - 1) return 0;
			return i < lenA - 1 ? -1 : 1;
		}
	}pam;

	char s[maxn];

	int main()
	{
		int t;
		scanf("%d", &t);
		while(t --)
		{
			int n, q, a, b, c, d;
			pam.init();
			scanf("%d%s", &n, s);
			for(int i = 0; i < n; i ++) pam.add(s[i] - 'a');
			scanf("%d", &q);
			while(q --)
			{
				scanf("%d%d%d%d", &a, &b, &c, &d);
				int res = pam.comp(a, b, c, d);
				if(res == 0) puts("draw");
				else if(res == 1) puts("cslnb");
				else puts("sjfnb");
			}
		}
		return 0;
	}
	```

## C. Tokitsukaze and Colorful Tree

## D. Tokitsukaze and Multiple

给一个序列，每次可以合并任意两个连续的点，权值改为他们的和，问若干次以后最多有多少个点是 p 的倍数。 n 1e5

贪心即可，取尽量少的数量和为 p 的倍数就一定会取。

做前缀 map，前缀和对 p 取模即可，每次找到一个前缀和相同的就清空 map 并把答案加一。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/28 12:09
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

	map<int, int> mp;

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        int n, p;
	        R(n, p);
	        int now = 0;
	        int res = 0;
	        mp.clear();
	        mp[0] = 1;
	        for (int i = 1; i <= n; ++i) {
	            int x;
	            R(x);
	            now += x;
	            now %= p;
	            if (mp[now]) {
	                mp.clear();
	                res ++;
	            }
	            mp[now] = i;
	        }
	        W(res);
	    }
	    return 0;
	}
	```

## E. Little W and Contest

有两种人，一种写代码一种看题，求组成三人队伍起码有两个写代码的数量。有合并操作表示他们合并之后不能在同一个队伍。

考虑合并造成的影响即可，其实每次合并都在减小答案。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	typedef pair<int,int> pii;
	typedef pair<ll,ll> pll;
	const int maxn=1e6+5;
	const int mod=1e9+7;
	vector<ll> V;
	ll siz[maxn][3];
	int fa[maxn];
	int getfa(int n) {
	    return fa[n]==n?n:fa[n]=getfa(fa[n]);
	}
	int main() {
	    int T;cin>>T;while(T--) {
	        int n;cin>>n;ll cnt[3]={0,0,0};
	        for(int i=1;i<=n;i++) siz[i][1]=siz[i][2]=0,fa[i]=i;
	        for(int i=1;i<=n;i++) {
	            int x;scanf("%d",&x);
	            siz[i][x]=1;cnt[x]++;
	        }
	        ll ans=cnt[1]*cnt[2]*(cnt[2]-1)/2;
	        if(cnt[2]>=3) ans+=cnt[2]*(cnt[2]-1)*(cnt[2]-2)/6;
	        printf("%lld\n",ans%mod);
	        for(int i=1;i<n;i++) {
	            int u,v;scanf("%d%d",&u,&v);
	            u=getfa(u);v=getfa(v);
	            ans=ans-siz[u][1]*siz[v][2]*(cnt[2]-siz[u][2]-siz[v][2])
	                   -siz[u][2]*siz[v][2]*(cnt[2]-siz[u][2]-siz[v][2])
	                   -siz[u][2]*siz[v][2]*(cnt[1]-siz[u][1]-siz[v][1])
	                   -siz[u][2]*siz[v][1]*(cnt[2]-siz[u][2]-siz[v][2]);
	            printf("%lld\n",ans%mod);
	            fa[u]=v;siz[v][1]+=siz[u][1];siz[v][2]+=siz[u][2];
	        }
	    }
	    return 0;
	}
	```

## G. Tokitsukaze and Rescue

题意：一张完全图，边权随机，删k(k<=5，删完保证图联通)条边，问删完之后S到T的最短路最大值是多少。

每次暴力枚举最短路上的边删边，复杂度$O(n^klog^k(n)c^k)$，c为最短路上的边数，因为边权随机，c一定很小，暴力求解即可。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>

	using namespace std;

	const int maxn = 50 + 10;

	int head[maxn], dis[maxn], cnt;
	struct Edge{ int nex, to, w; bool vis; } edge[maxn * maxn];

	void add(int u, int v, int w)
	{
		edge[++ cnt].nex = head[u];
		edge[cnt].w = w;
		edge[cnt].to = v;
		edge[cnt].vis = false;
		head[u] = cnt;
	}

	pair<int, int> pre[maxn];

	void dij(int s)
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
				if(edge[i].vis) continue;
				int v = edge[i].to, w = edge[i].w;
				if(dis[u] + w < dis[v])
				{
					dis[v] = dis[u] + w;
					pre[v] = {u, i};    
					que.push({dis[v], v});
				}
			}
		}
	}

	int n, k, res;
	void dfs(int dep)
	{
		if(dep == k) 
		{
			dij(1);
			res = max(res, dis[n]);
			return;
		}
		dij(1);
		int now = n;
		vector<int> path;
		while(now != 1)
		{
			path.push_back(pre[now].second);
			now = pre[now].first;
		}
		for(auto x : path) 
		{
			edge[x].vis = edge[x ^ 1].vis = 1;
			dfs(dep + 1);
			edge[x].vis = edge[x ^ 1].vis = 0;
		}
	}

	int main()
	{
		int t;
		scanf("%d", &t);
		while(t --)
		{
			scanf("%d%d", &n, &k);
			cnt = -1;
			res = 0;
			memset(head, 0xff, sizeof head);
			for(int i = 1; i <= (n - 1) * n / 2; i ++)
			{
				int u, v, w;
				scanf("%d%d%d", &u, &v, &w);
				add(u, v, w);
				add(v, u, w);
			}
			dfs(0);
			printf("%d\n", res);
		}

		return 0;
	}
	```

## H. Triangle Collision

一个球在三角形里面跳，无能量损失，求 t 次碰撞经过的路程。

将三角形展开有循环节，二分求时间即可。理论上也可以直接计算。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>
	using namespace std;
	typedef long long ll;
	typedef pair<int,int> pii;
	typedef pair<ll,ll> pll;
	const int maxn=1e6+5;
	vector<ll> V;
	int pre[maxn];
	double L,x,y,vx,vy,h;int k;
	const double SQ3=sqrt(3);
	bool check(double t) {
	    ll cnt=0;
	    double nx=x+vx*t;
	    double ny=y+vy*t;
	    if(ny<=0) cnt++,ny=-ny;cnt+=(ll)(ny/h);
	    double x1=nx-1.0/SQ3*ny,
	    x2=nx+1.0/SQ3*ny;
	    if(x1>L/2) {
	        cnt+=1+(ll)(x1-L/2)/L;
	    }if(x2>L/2) {
	        cnt+=1+(ll)(x2-L/2)/L;
	    }
	    if(x1<-L/2) {
	        cnt+=1-(ll)(x1+L/2)/L;
	    }if(x2<=-L/2) {
	        cnt+=1-(ll)(x2+L/2)/L;
	    }
	    return cnt>=k;
	}
	int main() {
	    int T;cin>>T;while(T--) {
	        scanf("%lf%lf%lf%lf%lf%d",&L,&x,&y,&vx,&vy,&k);
	        h=SQ3*L/2;
	        double l=0,r=1e13;
	        while(r-l>0.00001){
	            double mid=(l+r)/2;
	            if(check(mid)) r=mid;
	            else l=mid;
	        }
	        printf("%.8f\n",l);
	    }
	    return 0;
	}
	```

## I. Parentheses Matching

有一些位置没有确定的括号序列，要使括号序列合法的最小字典序解。

找到未匹配左括号的可以放的最右点，和未匹配右括号可以放的最左边。

??? note "Code"
	```cpp
	#include <bits/stdc++.h>

	using namespace std;
	typedef long long ll;

	const int maxn = 1e5 + 10;
	char s[maxn];

	int main()
	{
	    int q;
	    scanf("%d", &q);
	    while(q --)
	    {
	        scanf("%s", s + 1);
	        int n = strlen(s + 1);
	        stack<int> l;
	        queue<int> que;
	        for(int i = 1; i <= n; i ++)
	        {
	            if(s[i] == '(') l.push(i);
	            else if(s[i] == ')')
	            {
	                if(l.empty()) que.push(i);
	                else l.pop();
	            }
	        }
	        bool flag = false;
	        for(int i = 1; i <= n; i ++)
	        {
	            if(que.empty()) break;
	            if(s[i] =='*') {
	                if(que.front() < i) {flag = true; break; } 
	                s[i] = '(';
	                que.pop();
	            } 
	        }
	        if(flag || !que.empty())
	        {
	            puts("No solution!");
	            continue;
	        }
	        while(!l.empty()) {que.push(l.top()); l.pop();}
	        for(int i = n; i >= 1; i --) 
	        {
	            if(que.empty()) break;
	            if(s[i] == '*') 
	            {
	                if(que.front() > i) {flag = true; break; }
	                s[i] = ')';
	                que.pop();
	            }
	        }
	        if(flag || !que.empty())
	        {
	            puts("No solution!");
	            continue;
	        }
	        for(int i = 1; i <= n; i ++) if(s[i] != '*') printf("%c", s[i]);
	        puts("");
	        

	    }
	    
	    return 0;
	}
	```