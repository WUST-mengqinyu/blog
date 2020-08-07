| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |   L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 1](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+1&source=1&searchmode=source) | 2020/7/21 | 7/12   |  .   |  .   |  .   |  O   |  O   |  Ø   |  .   |  .   |  Ø   |  Ø   |  Ø   |  Ø   |


## D. Distinct Sub-palindromes

求长度为 n 的任意串中，本质不同回文子串最少的有多少种

长度为 1,2,3 的时候随便填都是最少个数

大于三的只要取三个不同字符 abc 循环即可，最少不同回文子串为 3 个

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/21 12:20
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 1e5+50;
	const int mod = 998244353;
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

	int main(int argc, char* argv[]) {
	    int T;
	    scanf("%d", &T);
	    ll res = 1;
	    for (int i = 24; i <= 26; ++i) {
	        res = res * i % mod;
	    }
	    for (int kase = 1; kase <= T; ++kase) {
	        int n;
	        R(n);
	        if (n == 1) {
	            W(26);
	        } else if (n == 2) {
	            W(676);
	        } else if (n == 3) {
	            W(26*26*26);
	        } else {
	            W(res);
	        }
	    }
	    return 0;
	}
	```


## E. Fibonacci Sum

求 $\sum_{i=0}^N (F^K_{i*C})$ 对 1e9+7 取模

其中 $F_0 = 0, F_1 = 1, F_i=F_{i-1}+F_{i-2}$

众所周知 5 是 1e9+7 的原根所以随便做一下二次剩余来表示斐波那契数列通项公式即可。

$F_n = \frac{1}{\sqrt{5}}\left[(\frac{1+\sqrt{5}}{2})^n-(\frac{1-\sqrt{5}}{n})^n\right]$

两个常数项用二次剩余搞一搞就变成

$F_n = d(a^n-b^n)$

然后答案就是 $d^k \sum_{i=0}^N \left(a^{C*i}-b^{C*i}\right)^K$

n 很大要对其做二项式展开转换为与 k 相关的等比数列通项然后做快速幂即可。

快速幂可以对 1e9+8 取模做欧拉降幂来降低常数。

另外由于有多组数据本题复杂度出满其实是不能过的。


??? note "Code"
	```cpp
	#include <bits/stdc++.h>
	using namespace std; 
	typedef long long ll;
	const ll mod=1e9+9;
	const int maxn=1e5+5;
	ll C[maxn];
	ll inv[maxn],pr1[maxn],pr2[maxn];
	int cnt=0;
	inline ll fastpow(ll a,ll b){
	    if(a%mod==0) b=b%(mod-1)+mod-1;else b%=(mod-1);
	    ll ans=1;
	    for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	        return ans;
	}
	inline ll calc(ll x,ll n) {
	    if(x==1) return n%mod;
	    return (x*(1-fastpow(x,n))%mod*fastpow(1-x,mod-2)%mod+mod)%mod;
	}
	int main(){
	    clock_t start,end;
	    start=clock();
	    int T;cin>>T;
	    ll n,m,k;
	    inv[1] = 1;pr1[0]=pr2[0]=1;
	    for(int i=2;i<maxn;++i) inv[i]=(mod-mod/i)*inv[mod%i]%mod;
	    while (T--)    {
	        ll s=723398404,r1=308495997,r2=691504013,ans=0;
	        scanf("%lld%lld%lld",&n,&k,&m);
	        r1=fastpow(r1,k);r2=fastpow(r2,k);
	        C[0]=1;
	        for (register int i=1;i<=m;i++){
	            C[i]=C[i-1]*(m-i+1)%mod*inv[i]%mod;
	            pr1[i]=pr1[i-1]*r1%mod;pr2[i]=pr2[i-1]*r2%mod;
	        } 
	        for (int i=0;i<=m;i++) {
	            ll x=C[i];
	            x=x*calc(pr1[i]*pr2[m-i]%mod,n)%mod;
	            x*=((m-i)%2==1)?-1:1;
	            ans=(ans+x+mod)%mod;
	        }
	        ans=fastpow(s,m)*ans%mod;
	        printf("%lld\n",ans);
	    }
	        // cout<<cnt<<endl;
	    end=clock();
	    // cout<<(float)(end-start)*1000/CLOCKS_PER_SEC<<endl;
	    return 0;
	}
	```

## F. Finding a MEX

给一张图，有点权带修求一个点直接相邻的点的点权 mex，n,m,q 1e5 a 1e9，时限 3s

对点的度数分块即可。

询问对大点用树状数组维护所有的直接相邻点权，小点暴力所有临点。

修改对相邻的所有大点修改树状数组。

复杂度 $O(n\sqrt n * \log(n))$

关于树状数组上二分求 mex 做单 log 可以学习一下。貌似二分 check 做双 log 也可以通过

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/24 20:11
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

	const int BL = 350;

	int n, m;
	int a[maxn];
	VI edge[maxn], H[maxn], num[maxn];
	int id[maxn], up[BL], tot, big[maxn];
	vector<VI> BIT;

	inline void add(VI& now, int x, int k) {
	    x ++;
	    while (x < now.size()) {
	        now[x] += k;
	        x += x & -x;
	    }
	}

	inline int mex(int u) {
	    int ret = 0, ans = 0;
	    for (int i = up[id[u]]; i >= 0; --i) {
	        ans += 1 << i;
	        if (ans >= BIT[id[u]].size() || ret + BIT[id[u]][ans] < ans) ans -= 1 << i;
	        else ret += BIT[id[u]][ans];
	    }
	    return ret;
	}

	int main(int argc, char* argv[]) {
	//     freopen("data.in","r",stdin);
	//    freopen("data.out", "w", stdout);
	//    clock_t ST = clock();
	//    cerr << "time: " << ((clock() - ST) * 1000.0 / CLOCKS_PER_SEC) << "ms" << endl;
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        R(n, m);
	        BIT.clear();
	        tot = 0;
	        for (int i = 1; i <= n; ++i) edge[i].clear(), H[i].clear(), num[i].clear(), R(a[i]);
	        for (int i = 0; i < m; ++i) {
	            int u, v;
	            R(u, v);
	            edge[u].push_back(v);
	            edge[v].push_back(u);
	        }
	        for (int i = 1; i <= n; ++i) {
	            num[i].resize((int)edge[i].size());
	            if (edge[i].size() >= BL) {
	                big[i] = 1;
	                BIT.emplace_back(VI(edge[i].size() + 2));
	                up[tot] = log2(edge[i].size() + 1);
	                id[i] = tot;
	                tot ++;
	            } else big[i] = 0;
	            for (auto j : edge[i]) {
	                if (edge[j].size() >= BL) H[i].push_back(j);
	                if (a[j] < (int)edge[i].size()) {
	                    if (++num[i][a[j]] == 1 && big[i]) add(BIT.back(), a[j], 1);
	                }
	            }
	        }
	        int q;
	        R(q);
	        while (q--) {
	            int op, u, x;
	            R(op, u);
	            if (op == 1) {
	                R(x);
	                for (auto v : H[u]) {
	                    if (a[u] < (int)edge[v].size()) if (--num[v][a[u]] == 0) add(BIT[id[v]], a[u], -1);
	                    if (x < (int)edge[v].size()) if (++num[v][x] == 1) add(BIT[id[v]], x, 1);
	                }
	                a[u] = x;
	            } else {
	                if (!big[u]) {
	                    int res = edge[u].size();
	                    for (int i = 0; i < edge[u].size(); ++i) num[u][i] = 0;
	                    for (auto v : edge[u]) if (a[v] < edge[u].size()) num[u][a[v]] ++;
	                    for (int i = 0; i < edge[u].size(); ++i) if (num[u][i] == 0) {
	                        res = i;
	                        break;
	                    }
	                    W(res);
	                } else {
	                    W(mex(u));
	                }
	            }
	        }
	    }
	    return 0;
	}
	```

## I. Leading Robots

*upsolved by: Verly*

题意：有n个机器人，t时刻的位置为$at^2+p$，问有多少个机器人处于过领先状态，当且仅当处于最前的机器人唯一时才视为领先。

令$x=t^2$，则$y=ax+p$，问有多少条射线在某一时刻处于最上方，也就是BZOJ1007的问题。维护一个单调递增的下凸包，看栈中有多少点即可。

这道题需要注意的是直线的交点可能位于y轴的左侧，这种情况是不合法的，需要做一下预处理。对于相同的p只保留最大的a，且对于$p_1<p_2$保证$a_1>a_2$，被丢弃的数据不会对答案产生贡献，处理后的数据一定能保证直线的交点在y轴右侧。

在计算完后需要减去出现多次的ab点对对答案的贡献。

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;
    
    const int maxn = 5e4 + 10;
    
    vector<pair<int, int> > ve, tmp;
    int st[maxn];
    bool vis[maxn];
    
    bool cmp(pair<int, int> a,pair<int, int> b,pair<int, int> c)
    {
        return 1ll * (a.second - b.second) * (c.first - a.first) <= 1ll * (a.second - c.second) * (b.first - a.first); 
    }


    int main()
    {
        int t;
        scanf("%d", &t);
        while(t --)
        {
            int n;
            scanf("%d", &n);
            tmp.clear(); ve.clear(); 
            for(int i = 0; i < n; i ++) vis[i] = false;
            for(int i = 1; i <= n; i ++) 
            {
                pair<int, int> t;
                scanf("%d%d", &t.first, &t.second);
                tmp.push_back(t);
            }
            sort(tmp.begin(), tmp.end());
            for(int i = n - 1; i >= 0; i --)
            {
                pair<int, int> t = {tmp[i].second, tmp[i].first};
                if(ve.size() > 0 && t.second == ve.back().second && t.first == ve.back().first) vis[ve.size() - 1] = true;
                if(!ve.size()) ve.push_back(t); 
                else if(t.second == ve.back().second) continue;  
                else if(t.first > ve.back().first) ve.push_back(t);
            }
            sort(ve.begin(), ve.end());
            int top = 0, dsc = 0;
            for(int i = 0; i < (int)ve.size(); i ++)
            {
                while(top)
                {
                    if(top > 1 && cmp(ve[st[top - 1]], ve[i], ve[st[top]])) top --;
                    else break;
                }
                st[++ top] = i;
            }
            for(int i = 1; i <= top; i ++) 
            {
                if(vis[st[i]]) dsc ++;
            }
            printf("%d\n", top - dsc);
        }
        return 0;
    }
    ```

## J. Math is Simple

*upsolved by: ffacs*


题意：求 
$$
\sum\limits_{1\le a < b \le n\\gcd(a,b)=1\\a+b \ge n}{\frac{1}{ab}}
$$
$T\le1e4,2\le n\le 1e8$ ，输出模 $998244353$ 意义下的值，**时限六秒**

这个 $n$ 好像不是很大啊，能不能递推捏？下面这个 大于等于号也太烦了，变成等于才舒服。

设 
$$
f_n=\sum\limits_{1\le a < b \le n\\gcd(a,b)=1\\a+b \ge n}{\frac{1}{ab}}
$$
来考虑一下 $f_n$ 比 $f_{n-1}$ 多加上了什么东西。
$$
\begin{align}
f_n-f_{n-1}&=\sum\limits_{1\le a < b=n\\gcd(a,b)=1\\a+b \ge n}{\frac{1}{ab}}-\sum\limits_{1\le a < b \le n-1\\gcd(a,b)=1\\a+b = n-1}{\frac{1}{ab}} \\
&=\frac{1}{n}\sum_{1\le a\le n\\gcd(a,n)=1}\frac{1}{a}-\sum\limits_{1\le a < b \le n-1\\gcd(a,b)=1\\a+b = n-1}{\frac{1}{ab}} \\
\end{align}
$$
现在都是等号了，右边那个太丑了，简化一下，不妨设 
$$
g(n)=\sum\limits_{1\le a < b \le n\\gcd(a,b)=1\\a+b = n}{\frac{1}{ab}}
$$
这样 $n-1$ 换成 $n$ 比较方便，因为和是定值，我们只枚举 $a$ 即可，又有 $(a,b)=(a,n-a)=(a,n)$ ,$\frac{1}{ab}=\frac{1}{a(n-a)}=\frac{1}{n}(\frac{1}{a}+\frac{1}{n-a})$
$$
\begin{align}
g(n)&=\frac{1}{n}\sum_{1\le a<n-a \le n\\(a,n)=1}(\frac{1}{a}+\frac{1}{n-a})
\end{align}
$$
发现在不考虑  $(a,n)=1$的时候 除了 $a=n-a$ ，所有 $\frac{1}{a},1\le a\le n-1$ 都遍历到了，而 $a=n-a$ 和 $a=n$ 时， $(a,n)\neq 1$ ，还有要注意 $n=2$ 的时候是不成立的。所以可以改写成
$$
g(n)=\frac{1}{n}\sum_{1\le a \le n\\gcd(a,n)=1}\frac{1}{a}
$$
这个和 $(4)$ 中的第一项居然是一样的。也就是说我们得到了 
$$
f_n-f_{n-1}=g_n-g_{n-1} \\
f_n-f_2=g_n-g_2 \\
f_n=g_n+\frac{1}{2}
$$
其中 
$$
g_n=
\left\{
\begin{array}{**lr**}
	\frac{1}{n}\sum\limits_{1\le a \le n\\gcd(a,n)=1}\frac{1}{a} \\
	0,n=2\\
\end{array}
\right.
$$
这个 $g(n)$ 看起来就很好求
$$
\begin{align}
g(n)&=\frac{1}{n}\sum_{1\le a\le n}\frac{1}{a}\sum_{d\mid gcd(a,n)}\mu(d) \\
&=\frac{1}{n}\sum_{d\mid n}\mu(d)\sum_{d\mid a}\frac{1}{a} \\
&=\frac{1}{n}\sum_{d\mid n}\mu(d)\sum_{a=1}^{\lfloor\frac{n}{d}\rfloor}\frac{1}{ad} \\
&=\frac{1}{n}\sum_{d\mid n}\mu(d)\frac{1}{d}\sum_{a=1}^{\lfloor\frac{n}{d}\rfloor}\frac{1}{a}
\end{align}
$$

后面就是一个调和级数前缀和，又因为里面有 $\mu(d)$ 又要求是 $n$ 的因子，所以我们直接  $\text{dfs}$ 素因子最多出现一次的因子即可。

## K. Minimum Index

*upsolved by: Verly*

推荐阅读 [金策-字符串算法选讲](https://www.docin.com/p-1936795644.html) 学习一下Lyndon循环。

对于S的某个前缀$s[0,k]$，把它分为$S[0,i-1]$和$S[i,k]$，其中$s[0,i-1]$由$s_1s_2...s_g$组成，且$s_1...s_{g}$为$s_{g}≤s_{g-1}≤..≤s_1$的Lyndon串，且有$S[i,k]<s_g$，$S[i,k]=t_1t_2...t_hv$，其中$t_1=t_2=...=t_h$，且$v$为$t_1$的真前缀，$j=k-|t_1|$。

所以在check循环节时：

- 如果$S[j]<S[k]$，也就是出现了形如$abcabcabz$的情况$(i=0, j=5, k=8)$，此时的答案为所有循环串的开头，$res[k]=i$
- 如果$S[j]≥S[k]$，即$abcabcabc$或者$abcabcabd(i=0,j=5,k=8,res[j]=3)$，此时的答案为最近的一个循环串的串首，$res[k]=res[j]+k-j$

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    const int maxn = 1e6 + 10;
    const int mod = 1e9 + 7;
    char s[maxn];
    int res[maxn];

    void duval(char s[])
    {
        int n = strlen(s), i = 0;
        while(i < n)
        {
            int j = i, k = i + 1;
            res[i] = i;
            while(k < n && s[j] <= s[k])
            {
                if(s[j] < s[k]) j = i, res[k] = i;
                else res[k] = res[j] + k - j, j ++;
                k ++;
            }
            while(i <= j) i += k - j;
        }
    }

    int main()
    {
        int t;
        scanf("%d", &t);
        while(t --)
        {
            scanf("%s", s);
            int n = strlen(s);
            duval(s);
            ll ans = 0;
            for(int i = 0, p = 1; i < n; i ++, p = 1ll * p * 1112 % mod) 
                ans = (ans + 1ll * p * (res[i] + 1)) % mod;
            printf("%lld\n", ans);
        }
        return 0;
    }
    ```

## L. Mow

给一个凸包，你可以每个单位面积用 A 的代价涂色，或者用一个半径为 r 的圆形的区域（不能超出边界）给一个单位面积以 B 的代价涂色，求全部涂满色的最少花费。

考虑圆心的范围是凸包每条边往内移动 r 距离构成的新凸包。如果 A<B 显然全部用 A 涂色即可，直接算原凸包面积，否则尽量用 B 涂色，最大范围是 $新凸包面积+新凸包周长*r+pi*r*r$。

可以考虑非扇形的区域实际是平行线做切割一共是新凸包周长那么长的，扇形区域拼起来就是一个外角和为 2pi。

所以首先把凸包处理成逆时针，每条边用向量表示的话，向左旋转 pi/2 并表示为单位向量即是它的单位法向量，往这个移动 r 的距离，然后做半平面交求出新凸包的点集，注意如果新凸包点集 <= 2 其实表示它不存在。

??? note "Code"
	```cpp
	/*================================================================
	*
	*   创 建 者： badcw
	*   创建日期： 2020/7/25 22:34
	*
	================================================================*/
	#include <bits/stdc++.h>

	#define VI vector<int>
	#define ll long long
	using namespace std;

	const int maxn = 205;
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
	db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
	db rad(point k1,point k2){return atan2(cross(k1,k2),dot(k1,k2));}
	// -pi -> pi
	int compareangle (point k1,point k2){
	    return k1.getP()<k2.getP()||(k1.getP()==k2.getP()&&sign(cross(k1,k2))>0);
	}
	point proj(point k1,point k2,point q){ // q 到直线 k1,k2 的投影
	    point k=k2-k1; return k1+k*(dot(q-k1,k)/k.abs2());
	}
	point reflect(point k1,point k2,point q){return proj(k1,k2,q)*2-q;}
	int clockwise(point k1,point k2,point k3){// k1 k2 k3 逆时针 1 顺时针 -1 否则 0
	    return sign(cross(k2-k1,k3-k1));
	}
	int checkLL(point k1,point k2,point k3,point k4){// 求直线 (L) 线段 (S)k1,k2 和 k3,k4 的交点
	    return cmp(cross(k3-k1,k4-k1),cross(k3-k2,k4-k2))!=0;
	}
	point getLL(point k1,point k2,point k3,point k4){
	    db w1=cross(k1-k3,k4-k3),w2=cross(k4-k3,k2-k3); return (k1*w2+k2*w1)/(w1+w2);
	}
	int intersect(db l1,db r1,db l2,db r2){
	    if (l1>r1) swap(l1,r1); if (l2>r2) swap(l2,r2); return cmp(r1,l2)!=-1&&cmp(r2,l1)!=-1;
	}
	int checkSS(point k1,point k2,point k3,point k4){
	    return intersect(k1.x,k2.x,k3.x,k4.x)&&intersect(k1.y,k2.y,k3.y,k4.y)&&
	           sign(cross(k3-k1,k4-k1))*sign(cross(k3-k2,k4-k2))<=0&&
	           sign(cross(k1-k3,k2-k3))*sign(cross(k1-k4,k2-k4))<=0;
	}
	db disSP(point k1,point k2,point q){
	    point k3=proj(k1,k2,q);
	    if (inmid(k1,k2,k3)) return q.dis(k3); else return min(q.dis(k1),q.dis(k2));
	}
	db disSS(point k1,point k2,point k3,point k4){
	    if (checkSS(k1,k2,k3,k4)) return 0;
	    else return min(min(disSP(k1,k2,k3),disSP(k1,k2,k4)),min(disSP(k3,k4,k1),disSP(k3,k4,k2)));
	}
	int onS(point k1,point k2,point q){return inmid(k1,k2,q)&&sign(cross(k1-q,k2-k1))==0;}
	struct circle{
	    point o; db r;
	    void scan(){o.scan(); scanf("%lf",&r);}
	    int inside(point k){return cmp(r,o.dis(k));}
	};
	struct line{
	    // p[0]->p[1]
	    point p[2];
	    line(point k1,point k2){p[0]=k1; p[1]=k2;}
	    point& operator [] (int k){return p[k];}
	    int include(point k){return sign(cross(p[1]-p[0],k-p[0]))>0;}
	    point dir(){return p[1]-p[0];}
	    line push(){ // 向外 ( 左手边 ) 平移 eps
	        const db eps = 1e-6;
	        point delta=(p[1]-p[0]).turn90().unit()*eps;
	        return {p[0]-delta,p[1]-delta};
	    }
	};
	point getLL(line k1,line k2){return getLL(k1[0],k1[1],k2[0],k2[1]);}
	int parallel(line k1,line k2){return sign(cross(k1.dir(),k2.dir()))==0;}
	int sameDir(line k1,line k2){return parallel(k1,k2)&&sign(dot(k1.dir(),k2.dir()))==1;}
	int operator < (line k1,line k2){
	    if (sameDir(k1,k2)) return k2.include(k1[0]);
	    return compareangle(k1.dir(),k2.dir());
	}
	int checkpos(line k1,line k2,line k3){return k3.include(getLL(k1,k2));}
	vector<point> halfPlaneIS(vector<line> &l) {
	    sort(l.begin(), l.end());
	    deque<line> q;
	    for (int i = 0; i < (int)l.size(); ++i) {
	        if (i && sameDir(l[i], l[i - 1])) continue;
	        while (q.size() > 1 && !checkpos(q[q.size() - 2], q[q.size() - 1], l[i])) q.pop_back();
	        while (q.size() > 1 && !checkpos(q[1], q[0], l[i])) q.pop_front();
	        q.push_back(l[i]);
	    }
	    while (q.size() > 2 && !checkpos(q[q.size() - 2], q[q.size() - 1], q[0])) q.pop_back();
	    while (q.size() > 2 && !checkpos(q[1], q[0], q[q.size() - 1])) q.pop_front();
	    vector<point> ret;
	    for (int i = 0; i < (int)q.size(); ++i) ret.push_back(getLL(q[i], q[(i + 1) % q.size()]));
	    return ret;
	}
	db area(vector<point> A){ // 多边形用 vector<point> 表示 , 逆时针
	    db ans=0;
	    for (int i=0;i<A.size();i++) ans+=cross(A[i],A[(i+1)%A.size()]);
	    return ans/2;
	}

	int main(int argc, char* argv[]) {
	//     freopen("data.in","r",stdin);
	//    freopen("my.out", "w", stdout);
	//    clock_t ST = clock();
	    int T;
	    scanf("%d", &T);
	    for (int kase = 1; kase <= T; ++kase) {
	        int n;
	        db r, A, B;
	        R(n, r, A, B);
	        vector<point> x(n);
	        for (int i = 0; i < n; ++i) x[i].scan();
	        db s = area(x);
	        if (sign(s) < 0) {
	            reverse(x.begin(), x.end());
	            s = -s;
	        }
	        vector<line> deal;
	        for (int i = 0; i < n; ++i) {
	            point w = (x[(i + 1) % n] - x[i]).turn90().unit();
	            deal.emplace_back(line(x[i] + w * r, x[(i + 1) % n] + w * r));
	        }
	        auto real = halfPlaneIS(deal);
	        db res = s * A;
	        if (real.size() > 2) {
	            db realv = area(real);
	            db tmp = 0;
	            for (int i = 0; i < real.size(); ++i) tmp += real[i].dis(real[(i+1)%real.size()]);
	            db all = (realv + tmp * r + r * r * pi);
	            res = min(res, all * B + (s - all) * A);
	        }
	        W(res);
	    }
	//    cerr << "time: " << ((clock() - ST) * 1000.0 / CLOCKS_PER_SEC) << "ms" << endl;
	    return 0;
	}
	```