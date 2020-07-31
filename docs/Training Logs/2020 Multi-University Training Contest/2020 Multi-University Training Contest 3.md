| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 3](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+3&source=1&searchmode=source) | 2020/7/28 | 7/11   |  Ø   |  .  |  Ø   |  O   |  O   |  .   |  Ø   |  O   |  O   |  .   |  .  |

## A. Tokitsukaze, CSL and Palindrome Game

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