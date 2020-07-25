| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |   L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 1](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+1&source=1&searchmode=source) | 2020/7/21 | 5/12   |  .   |  .   |  .   |  O   |  O   |  Ø   |  .   |  .   |  Ø   |  .   |  Ø   |  .   |


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
