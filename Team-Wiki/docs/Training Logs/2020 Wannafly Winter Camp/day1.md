

总之没有什么盐分，强调安全问题



## 下午比赛

签到飞快，2 题 rank1，最后一小时回去收拾东西然后鸽了，走的时候 rank8，最后 rank12

| Name                                                         |   Date    | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |
| ------------------------------------------------------------ | :-------: | :----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 CCPC Wannafly Winter Camp Day1 (Div.1&2)](https://codeforces.com/group/6QKpZkKhsL/contest/265753) | 2020/1/12 |  7/10  |  O   |  O   |  O   |  .   |  O   |  O   |  .   |  O   |  O  |  .  |

## To-do list

`E`


## A. 期望逆序对

求一个排列，排序一个区间对使得期望逆序对最少求期望。即对于 $[l_i,r_i]$ 中的任何一个整数 $j$，$x_i=j$的概率都是 $(r_i-l_i+1)^{-1}$

显然，对于两个区间 $[a,b]$ 和 $[c,d]$。若 $a + b < c + d$，显然  $[a,b]$ 应该在 $[c,d]$ 前面然后由于这个东西是单向有可传递性的所以直接对区间按权排序，然后计算期望即可

由于 $n\le 5\cdot 10^3$ 计算期望的方法是对于每个点对求它可能是逆序对的期望然后求和即可

所以本题考虑清楚每个点对的期望即可

??? note "Code"
    ```cpp
    /*================================================================
    *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
    *
    *   创 建 者： badcw
    *   创建日期： 2020/1/12
    *
    ================================================================*/
    #include <bits/stdc++.h>

    #define ll long long
    using namespace std;
    
    const int maxn = 5e3+50;
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
    
    int n;
    int l[maxn], r[maxn];
    int idx[maxn];
    ll inv[maxn];
    
    ll cal(int i, int j) {
        i = idx[i], j = idx[j];
        ll a = l[i], b = r[i], c = l[j], d = r[j];
        ll res = 0;
        if (c >= b) ;
        else if (c <= a && d >= b) {
            res = (a - c) * (b - a + 1) + (b - a + 1) * (b - a) / 2;
        } else if (a <= c && d <= b) {
            res = (b * 2 - c - d) * (d - c + 1) / 2;
        } else if (a <= c && d >= b) {
            res = (b - c) * (b - c + 1) / 2;
        }
        return res % mod * inv[i] % mod * inv[j] % mod;
    }
    
    int main(int argc, char* argv[]) {
    //    freopen("data.in", "r", stdin);
    //    freopen("data.out", "w", stdout);
    //    clock_t ST = clock();
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &l[i], &r[i]), idx[i] = i;
            inv[i] = qp(r[i] - l[i] + 1, mod - 2);
        }
        sort(idx + 1, idx + 1 + n, [](int x, int y) {
            return l[x] + r[x] < l[y] + r[y];
        });
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                res = (res + cal(i, j)) % mod;
            }
        }
        printf("%lld\n", res % mod);
    //    cerr << "time: " << ((clock() - ST) * 1000.0 / CLOCKS_PER_SEC) << "ms" << endl;
        return 0;
    }
    ```

## B. 密码学

有个加模的加密方法，输入加密 $m$ 次后每个串的形式，求原串

签到题，减模倒推即可

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    ```

    开营仪式using namespace std;
    typedef long long ll;
    
    const int maxn = 1000 + 10;
    char s[maxn][110];
    
    int x[maxn], y[maxn];
    
    int getid(char c)
    {
        if(c >= 'a' && c <= 'z') return c - 'a';
        if(c >= 'A' && c <= 'z') return c - 'A' + 26;
    }
    
    int getch(int c)
    {
        if(c >= 0 && c <= 25) return c + 'a';
        return c - 26 + 'A';
    }
    
    int len[maxn];
    
    int main()
    {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; i ++)
            scanf("%d%d", &x[i], &y[i]);
        for(int i = 1; i <= n; i ++) 
        {
            scanf("%s", s[i]);
            len[i] = strlen(s[i]);
        }
        for(int i = m; i >= 1; i --)
        {
            int nx = x[i], ny = y[i], lenx = len[nx], leny = len[ny];
            for(int i = 0; s[ny][i]; i ++)
            {
                char a = s[nx][i % lenx], b = s[ny][i];
                int z = (getid(b) + 52 - getid(a)) % 52;
                s[ny][i] = getch(z);
            }
        }
        for(int i = 1; i <= n; i ++) printf("%s\n", s[i]);
        return 0;
    }
    
    ```


## C. 染色图

令 $g(n,k)$ 为 $n$ 个点的无向图对点染成 $k$ 种颜色最多的边数，求 $\sum_{i=l}^{r} g(n,i)$
$$
g(n,i)=\frac{n^2-\sum_{i=l}^r{(\lceil\frac{n}{i}\rceil)}^2\cdot(n\%i)+{\lfloor\frac{n}{i}\rfloor}^2\cdot(i-n\%i)}{2}
$$

对该式分块，当$i\le\sqrt{n}$时对每个点单点求值，当$i\ge\sqrt{n}$时对$\lfloor\frac{n}{i}\rfloor$分块求和，其中$\sum_{i=l}^ri$和$n\%i$均为等差数列，而$\lfloor\frac{n}{i}\rfloor$在单个块内相等，每次求$l-1,r$的前缀和差分即可。

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    
    #define int ll
    
    const int mod = 998244353;
    
    ll qp(ll a, ll n = mod - 2)
    {
        ll ans = 1, base = a;
        while(n)
        {
            if(n & 1) (ans *= base) %= mod;
            (base *= base) %= mod;
            n >>= 1;
        }
        return ans;
    }
    
    signed main()
    {
        int t;
        scanf("%lld", &t);
        while(t --)
        {
            ll n, l, r;
            scanf("%lld%lld%lld", &n, &l, &r);
            int m = sqrt(n);
            ll res = 0;
            res = 1ll * n * n % mod * (r - l + 1) % mod;
            if(m > r) m = r;
            for(int i = l; i <= m; i ++)
            {
                res = (res - (n / i + 1) * (n / i + 1) % mod * (n % i) % mod + mod - (n / i) * (n / i) % mod * (i - n % i) % mod + mod) % mod;
            }
            if(m < l - 1) m = l - 1;
            int x = n / (m + 1), posl = m + 1;
            for(int i = x; i >= 1 && posl <= r; i --)
            {
                int posr = n / i;
                if(posr > r) posr = r;
                ll a = n % posl, b = n % posr;
                ll left = (a + b) * (posr - posl + 1) % mod * qp(2) % mod;
                ll right = ((posl + posr) * (posr - posl + 1) % mod * qp(2) % mod - left + mod) % mod;
                res = (res - 1ll * (i + 1) * (i + 1)  % mod * left % mod + mod - 1ll * i * i % mod * right % mod + mod) % mod;
                posl = posr + 1;
                if(posr == r) break;
            }
            res = res * qp(2) % mod;
            printf("%lld\n", res);
        }
        return 0;
    }
    ```

## E. 树与路径

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=500010;
    typedef long long LL;
    int n,m;
    struct edge{
        int b,nt;
    }e[N*2];
    int p[N],nn;
    int fa[N][32];
    LL f[N],g[N],h[N];
    void anode(int x,int y){
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;
        swap(x,y);
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;
    }
    int deep[N];
    void dfsLCA(int x,int ff=-1,int dd=0){
        for(int i=1;(1<<i)<=dd;i++){
            fa[x][i]=fa[ fa[x][i-1] ][i-1];
        }
        deep[x]=dd;
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==ff)continue;
            fa[t][0]=x;
            dfsLCA(t,x,dd+1);
        }
    }
    int LCA(int x,int y){
        if(deep[x]<deep[y])swap(x,y);
        int t=deep[x]-deep[y];
        for(int i=0;(1<<i)<=t;i++)if(t&(1<<i))x=fa[x][i];
        if(x==y)return y;
        for(int i=30;i>=0;i--){
            if(fa[x][i]!=fa[y][i]){
                x=fa[x][i];
                y=fa[y][i];
            }
        } 
        return fa[x][0];
    }
    int findf(int x,int d){
        for(int i=0;(1<<i)<=d;i++)if(d&(1<<i))x=fa[x][i];
        return x;
    }
    LL ans[N];
    void dfs1(int x){
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa[x][0])continue;
            dfs1(t);
            g[x]+=g[t];
            h[x]+=h[t];
        }
        g[x]+=h[x];
    }
    void dfs2(int x){
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa[x][0])continue;
            dfs2(t);
            f[x]+=f[t];
        }
        f[x]+=g[x];
    }
    void getAns(int x,LL now){
        ans[x]=now;
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa[x][0])continue;
            getAns(t,now-g[t]);
        }
    }
    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d%d",&n,&m);
        for(int i=1;i<n;i++){
            int aa,bb;
            scanf("%d%d",&aa,&bb);
            anode(aa,bb);
        }
        dfsLCA(1);
        LL asum=0;
        for(int i=1;i<=m;i++){
            int aa,bb;
            scanf("%d%d",&aa,&bb);
            if(aa==bb)continue;
            if(fa[aa][0]==bb||fa[bb][0]==aa)continue;
            int cc=LCA(aa,bb);
            int dis=2*deep[cc]-deep[aa]-deep[bb];dis=-dis;
            if(deep[aa]<deep[bb])swap(aa,bb);
            f[aa]+=dis-1;f[bb]+=dis-1;
            if(bb==cc){
                g[aa]+=dis-1;
                g[cc]+=dis-1;
                h[fa[aa][0]]-=2;
                h[cc]+=2;
            }else
            {
                g[aa]+=dis-1;
                h[fa[aa][0]]-=2;h[cc]-=2ll*(deep[aa]-deep[cc]-1)+1-dis;
                g[bb]+=dis-1;
                h[fa[bb][0]]-=2;h[cc]-=2ll*(deep[bb]-deep[cc]-1)+1-dis;
                h[cc]+=2;g[cc]-=2;
            }
            asum += 1ll*(deep[aa]-deep[cc])*(deep[bb]-deep[cc]);
        }
        dfs1(1);
        dfs2(1);
        getAns(1,asum);
        for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
        return 0;
    } 
    ```


## F. 乘法

给出两个序列，求全积中第 $k$ 大的数

二分答案，然后对答案进行 check，每次求比当前二分的答案小的数的个数，可以考虑将 $B$ 序列排序，枚举所有 $A$ 套一层二分求出小于它的数的个数即可

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=100010;
    typedef long long LL;
    int n,m;LL k;
    LL MAXN = 1000000000000000ll;
    LL A[N],B[N];
    int L,R;

    int findf(int f,LL x,LL y){
        //yz=x;
        if(!f){
            LL l=1,r=m,rtn=0;
            while(l<=r){
                LL mid=l+r>>1;
                if(B[mid]*y>=x){
                    rtn=mid;l=mid+1;
                }else r=mid-1;
            }
            return rtn;
        }else{
            LL l=1,r=m,rtn=m+1;
            while(l<=r){
                LL mid=l+r>>1;
                if(B[mid]*y>=x){
                    rtn=mid;r=mid-1;
                }else l=mid+1;
            }
            return m-rtn+1;
        }
    }

    int check(LL x){
        LL cnt = 0;
        
        for(int i=1;i<=n;i++){
            
            if(A[i]==0){
                if(x<0)cnt+=m; 
            }else{
                int f = (A[i]>0);  
                
                cnt+=findf(f,x,A[i]);
            }
            
            
        }
        
        return cnt>=k;
    }

    LL solve(){
        LL l=-MAXN,r=MAXN,rtn=MAXN*10;
        while(l<=r){
            LL mid=l+r>>1;
            if(check(mid)){
                rtn=mid;l=mid+1;
            }else r=mid-1;
        }
        return rtn;
    }

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d%d%lld",&n,&m,&k);
        for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
        for(int i=1;i<=m;i++)scanf("%lld",&B[i]);
        sort(B+1,B+1+m);
        LL ans=solve();
        printf("%lld",ans);
        return 0;
    } 
    ```


## H. 最大公约数

求 $y$ 使得在 $[1,n]$ 中不存在 $gcd(i,k)=gcd(y,k)$

队友一看是个大数，因为如果 $n=500, k=1$ 显然是 $n$ 中所有的素数积

然后随便推一推设 $p$ 是 $n$ 中所有的素数集合，答案就是 $k \cdot \prod p$

??? note "Code"
    ```python
    T = int(input())


    def prim(x):
        for i in range(2, x):
            if (x % i == 0):
                return False
        return True


    for kase in range(T):
        n, k = map(int, input().split())
        ans = k
        for i in range(2, int(n / k) + 1):
            if prim(i):
                ans *= i
        print(ans)
    ```

## I. K小数查询

区间推平最大值 + 区间查询第 k 小

分块 + 二分答案复杂度可过

正解树套树不会写

另外区间推平最大值是 segment beats

??? note "Code"
    ```cpp
    /*================================================================
    *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
    *
    *   创 建 者： badcw
    *   创建日期： 2020/1/12
    *
    ================================================================*/
    #include <bits/stdc++.h>

    #define ll long long
    using namespace std;
    
    const int maxn = 8e4+50;
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
    
    const int maxb = 1005;
    const int inf = 8e4+50;
    int n, m;
    int belong[maxn], lpos[maxb], rpos[maxb];
    int val[maxn], lazy[maxn], op[maxb];
    int block;
    
    void rebuild(int idx) {
        for (int i = lpos[idx]; i <= rpos[idx]; ++i) {
            if (val[i] > op[idx]) val[i] = op[idx];
            lazy[i] = val[i];
        }
        sort(lazy + lpos[idx], lazy + rpos[idx] + 1);
    //    op[idx] = inf;
    }
    
    void update(int l, int r, int w) {
        if (belong[l] == belong[r]) {
            for (int i = l; i <= r; ++i) {
                if (val[i] > w) val[i] = w;
            }
            rebuild(belong[l]);
            return;
        }
        for (int i = l; i <= rpos[belong[l]]; ++i) {
            if (val[i] > w) val[i] = w;
        }
        for (int i = belong[l] + 1; i < belong[r]; ++i) {
            if (op[i] > w) op[i] = w;
        }
        for (int i = lpos[belong[r]]; i <= r; ++i) {
            if (val[i] > w) val[i] = w;
        }
        rebuild(belong[l]), rebuild(belong[r]);
    }
    
    int sz;
    
    void rebuild() {
        for (int i = 1; i <= sz; ++i) {
            op[i] = 0;
            for (int j = lpos[i]; j <= rpos[i]; ++j) {
    //            if (val[j] > op[i]) val[j] = op[i];
                lazy[j] = val[j];
                op[i] = max(op[i], val[j]);
            }
            sort(lazy + lpos[i], lazy + rpos[i] + 1);
    //        for (int j = lpos[i]; j <= rpos[i]; ++j) {
    //            printf("%d ", lazy[j]);
    //        }
    //        printf(" | ");
        }
    //    printf("\n");
    }
    
    bool check(int x, int l, int r, int w) {
        int res = 0;
        if (op[belong[l]] < x) {
            res += rpos[belong[l]] - l + 1;
        } else {
            for (int i = l; i <= rpos[belong[l]]; ++i) {
                if (val[i] < x) res ++;
            }
        }
        for (int i = belong[l] + 1; i < belong[r]; ++i) {
            if (op[i] < x) res += rpos[i] - lpos[i] + 1;
            else {
                res += lower_bound(lazy + lpos[i], lazy + rpos[i] + 1, x) - lazy - lpos[i];
            }
        }
        if (op[belong[r]] < x) {
            res += r - lpos[belong[r]] + 1;
        } else {
            for (int i = lpos[belong[r]]; i <= r; ++i) {
                if (val[i] < x) res ++;
            }
        }
        return res < w;
    }
    
    int query(int l, int r, int w) {
        if (belong[l] == belong[r]) {
            vector<int> tmp;
            for (int i = l; i <= r; ++i) {
                if (val[i] > op[belong[i]]) tmp.push_back(op[belong[i]]);
                else tmp.push_back(val[i]);
            }
            sort(tmp.begin(), tmp.end());
            return tmp[w - 1];
        }
        int L = 1, R = inf;
        int res = 0;
        while (L <= R) {
            int mid = L + R >> 1;
            if (check(mid, l, r, w)) {
                res = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        return res;
    }
    
    int main(int argc, char* argv[]) {
        scanf("%d%d", &n, &m);
    //    block = n;
        block = sqrt(n);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &val[i]);
            lazy[i] = val[i];
            belong[i] = (i - 1) / block + 1;
        }
        sz = (n - 1) / block + 1;
        for (int i = 1; i <= sz; ++i) {
            lpos[i] = 1 + (i - 1) * block;
            rpos[i] = i * block;
        }
        rpos[sz] = n;
        rebuild();
        int op, l, r, x;
        for (int i = 1; i <= m; ++i) {
            scanf("%d%d%d%d", &op, &l, &r, &x);
            if (op == 1) {
                update(l, r, x);
            } else {
                printf("%d\n", query(l, r, x));
            }
        }
        return 0;
    }
    ```