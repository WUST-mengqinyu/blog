## 早上讲课

Div2 数据结构，属实没有什么盐分，从栈到线段树

最大收货是明确了 Segment Beats 的复杂度是 O(nlogn)，可以放心的使用线段树进行区间推平操作

## 下午比赛

| Name                                                         |   Date    | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |
| ------------------------------------------------------------ | :-------: | :----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 CCPC Wannafly Winter Camp Day2 (Div.1&2)](https://codeforces.com/group/6QKpZkKhsL/contest/265634) | 2020/1/13 |  7/11  |  O   |  .   |  O   |  .   |  O   |  O   |  .   |  O   |  .   |  O   |  O   |

仍然在前 20 名，很多串和图题，还是有点难顶

## To-do list

`C/F/J/K`

## A. 托米的字符串

求所有子串中元音字母占比的平均值

显然 $ans=\sum{\frac{x}{len}}$，若对单点计算贡献，那么 $ans_i = \sum\frac{1}{len}$

考虑这样的情况

`(1------i----n)`

其中 `[1,i]` 长度为 `x`， `[i,n]` 长度为 `y`，设 $x \le y$ 显然对于 `[1,x]` 长度的串每个都有期望 1，然后对于 `[x+1,y]` 的串期望个数为 `x`。计算式为：$\sum_{i=x+1}^{y}\frac{x}{i}$，对于 `[y+1,x+y-1]` 的串期望为 `[x-1,1]` 计算式为：$\sum_{i=y+1}^{x+y-1}\frac{x+y-i}{i}$ 化简为 ${x+y}\cdot\sum_{i=y+1}^{x+y-1}\frac{1}{i}-\sum_{i=y+1}^{x+y-1}1$ 对于 $\frac{1}{i}$ 求前缀和即可

如果 $x > y$ 可以考虑交换，因为它们有对称性

??? note "Code"
    ```cpp
    /*================================================================
    *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
    *
    *   创 建 者： badcw
    *   创建日期： 2020/1/13
    *
    ================================================================*/
    #include <bits/stdc++.h>

    #define ll long long
    using namespace std;

    const int maxn = 1e6+50;
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


    struct Frac {
        ll a, b;
        void getJian() {
            ll gcd = abs(__gcd(a, b));
            a /= gcd;
            b /= gcd;
            if (b < 0) {
                a = -a;
                b = -b;
            }
        }
        Frac(ll a_ = 1, ll b_ = 1) {
            a = a_;
            b = b_;
            getJian();
        }
        Frac add(const Frac& oth) {
            ll bt = b * oth.b;
            ll at = a * oth.b + oth.a * b;
            return Frac(at, bt);
        }
        Frac multi(const Frac& oth) {
            a *= oth.a;
            b *= oth.b;
            getJian();
            return *this;
        }
        bool operator < (const Frac& oth) const {
            return a * oth.b < b * oth.a;
        }
        bool operator == (const Frac& oth) const {
            return a * oth.b == b * oth.a;
        }
        bool operator <= (const Frac& oth) const {
            return a * oth.b <= b * oth.a;
        }
    };

    char s[maxn];
    double pre[maxn];
    //double pre2[maxn];

    int main(int argc, char* argv[]) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        for (int i = 1; i <= len; ++i) {
            pre[i] = pre[i - 1] + 1.0 / i;
    //        pre2[i] = pre2[i - 1] + pre[i];
        }
        double res = 0;
        for (int i = 1; i <= len; ++i) {
            if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'y') {
                int x = i;
                int y = len - i + 1;
    //            res += x * pre[y] - pre2[x - 1];
                if (x > y) swap(x, y);
                res ++;
                res += x * (pre[y] - pre[x]);
                res += (x + y) * (pre[x + y - 1] - pre[y]);
    //            res += (y - x) - x * (pre[y] - pre[x]);
            }
        }
        res /= len + (double)len * (len - 1) / 2;
        printf("%.10f\n", res);
        return 0;
    }
    ```

## C. 纳新一百的石子游戏

    ??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=500010;
    typedef long long LL;
    int n,m;
    int cnt[100];
    LL nowx;

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d",&n);
        
        for(int i=1;i<=n;i++){
            LL aa;scanf("%lld",&aa);
            LL ans=0;
            if(aa>nowx)ans++;
            LL t=nowx^aa;int flag=-1;
            for(int i=62;i>=0;i--){
                if(t&(1ll<<i)){
                    flag=i;break;
                }
            }
            if(flag!=-1){
                ans+=cnt[flag];
            }
            for(int i=0;aa;i++){
                if(aa&1)cnt[i]++;
                aa>>=1;
            }
            nowx=t;
            printf("%lld\n",ans);
        }
        return 0;
    } 
    ```

## E. 阔力梯的树

给一颗带点权有根树

对于任意一颗子树定义它的结实程度为对它子树内所有节点的编号排序后获得数组 a, $\sum_{i=1}^{k-1}(a_{i+1}-a_i)^2$

显然考虑两个区间怎么合并，首先两个不交叉区间的元素不会互相影响权值，所以直接合并答案再加上边界的答案即可

直接考虑动态开点权值线段树合并即可

??? note "Code"
    ```cpp
    /*================================================================
    *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
    *
    *   创 建 者： badcw
    *   创建日期： 2020/1/13
    *
    ================================================================*/
    #include <bits/stdc++.h>

    #define ll long long
    using namespace std;

    const int maxn = 1e5+50;
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

    int root[maxn];
    int ls[1800000], rs[1800000];
    ll res[maxn];
    int sz = 0;

    struct node {
        int lnum, rnum;
        ll ans;
    }p[1800000];

    void pushup(int rt) {
        p[rt].ans = p[ls[rt]].ans + p[rs[rt]].ans;
        if (p[ls[rt]].lnum) p[rt].lnum = p[ls[rt]].lnum;
        else p[rt].lnum = p[rs[rt]].lnum;
        if (p[rs[rt]].rnum) p[rt].rnum = p[rs[rt]].rnum;
        else p[rt].rnum = p[ls[rt]].rnum;
        if (p[rs[rt]].lnum == 0 || p[ls[rt]].rnum == 0) return;
        p[rt].ans += (ll)(p[rs[rt]].lnum - p[ls[rt]].rnum) * (p[rs[rt]].lnum - p[ls[rt]].rnum);
    }

    void insert(int &k, int l, int r, int val){
        if (!k) k = ++sz;
        if (l == r) {
            p[k].lnum = p[k].rnum = val;
            p[k].ans = 0;
    //        sum[k] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (val <= mid) insert(ls[k], l, mid, val);
        else insert(rs[k], mid + 1, r, val);
        pushup(k);
    //    sum[k] = sum[ls[k]] + sum[rs[k]];
    }

    //int query(int k, int l, int r, int rank) {
    //    if (l == r) return l;
    //    int mid = (l + r) >> 1;
    //    if (sum[ls[k]] >= rank) return query(ls[k], l, mid, rank);
    //    else return query(rs[k], mid + 1, r, rank - sum[ls[k]]);
    //}

    int merge(int x, int y) {
        if (!x) return y;
        if (!y) return x;
        ls[x] = merge(ls[x], ls[y]);
        rs[x] = merge(rs[x], rs[y]);
        pushup(x);
    //    sum[x] = sum[ls[x]] + sum[rs[x]];
        return x;
    }

    int n;
    vector<int> edge[maxn];

    void dfs(int u) {
        insert(root[u], 1, n, u);
        for (auto v : edge[u]) {
            dfs(v);
            merge(root[u], root[v]);
        }
        res[u] = p[root[u]].ans;
    }

    int main(int argc, char* argv[]) {
        scanf("%d", &n);
        for (int i = 2; i <= n; ++i) {
            int rt;
            scanf("%d", &rt);
            edge[rt].push_back(i);
        }
        dfs(1);
        for (int i = 1; i <= n; ++i) {
            printf("%lld\n", res[i]);
        }
        return 0;
    }
    ```

## F. 采蘑菇的克拉莉丝

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=2000010;
    typedef long long LL;
    int n,m;
    struct edge{
        int b,nt,w;
    }e[N];

    int fa[N],wfa[N],sz[N];
    int dfn[N],tt;
    int p[N],nn;
    void anode(int x,int y,int z){
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;e[nn].w=z;
        swap(x,y);
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;e[nn].w=z;
    }
    void dfs(int x,int ff=0){
        dfn[x]=++tt;sz[x]=1;
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==ff)continue;
            fa[t]=x;wfa[t]=e[i].w;
            dfs(t,x);
            sz[x]+=sz[t];
        }
    }

    int ROOT,ls[N*2],rs[N*2];
    LL sum[N*2];
    int cnt;
    void build(int &rt,int l,int r){
        rt=++cnt;
        if(l==r)return;
        int mid=l+r>>1;
        build(ls[rt],l,mid);
        build(rs[rt],mid+1,r);
    }

    void pushup(int rt){
        sum[rt]=sum[ls[rt]]+sum[rs[rt]];
    }

    void update(int rt,int l,int r,int x,int v){
        if(l==r){
            sum[rt]+=v;
            return;
        }
        int mid=l+r>>1;
        if(x<=mid)update(ls[rt],l,mid,x,v);
        else update(rs[rt],mid+1,r,x,v);
        pushup(rt);
    }

    LL query(int rt,int l,int r,int x,int y){
        if(l==x&&r==y)return sum[rt];
        int mid=l+r>>1;
        if(y<=mid)return query(ls[rt],l,mid,x,y);
        else if(x>mid)return query(rs[rt],mid+1,r,x,y);
        else return query(ls[rt],l,mid,x,mid)+query(rs[rt],mid+1,r,mid+1,y);
    }

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d",&n);
        for(int i=1;i<n;i++){
            int aa,bb,cc;
            scanf("%d%d%d",&aa,&bb,&cc);
            anode(aa,bb,cc);
        }
        dfs(1);
        build(ROOT,1,n);
        
        scanf("%d",&m);
        int nowR=1;
        for(int tk=1;tk<=m;tk++){
            int op;scanf("%d",&op);
            if(op==1){
                int aa,bb;
                scanf("%d%d",&aa,&bb);
                update(ROOT,1,n,dfn[aa],bb);
            }else{
                int aa;scanf("%d",&aa);
                nowR=aa;
            }
            
            LL ans=0;
            for(int i=p[nowR];i;i=e[i].nt){
                int t=e[i].b;
                if(t==fa[nowR])continue;
                ans+=1ll*e[i].w*query(ROOT,1,n,dfn[t],dfn[t]+sz[t]-1);
            }
            
            ans+=1ll*wfa[nowR]*(sum[ROOT]-query(ROOT,1,n,dfn[nowR],dfn[nowR]+sz[nowR]-1) ) ;
            printf("%lld\n",ans);
        }
        return 0;
    } 
    ```

## H. 叁佰爱抠的序列

题意相当于求一个最大的 m 使得 m 个点的完全图可以通过一条长度不超过 n - 1 的路径通过所有的边

显然对于 m 为奇数时，完全图中每个点的度数为偶数，则必然存在一条欧拉路使得通过所有点

对于 m 为偶数时，对于每个奇偶点多连一条边就可以使得每个点的度数变为偶数，就可以通过欧拉路求解

欧拉路算法为： `fleury`

m 为偶数时 n 最大为 `m * m / 2`

m 为奇数时 n 最大为 `m * (m - 1) / 2 + 1`

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    #define ll long long
    using namespace std;

    const int N=2010;
    const int mod = 1e9+7;
    ll n;

    ll cal2(ll x) { return x * x / 2; }
    ll cal1(ll x) { return x * (x - 1) / 2 + 1; }

    struct edge{
        int a,b,nt,pre;
    }e[N*N];
    int p[N],nn;
    void anode(int x,int y){
        e[nn].b=y;e[nn].nt=p[x];if(p[x]!=-1)e[p[x]].pre=nn;p[x]=nn;e[nn].a=x;e[nn].pre=-1;nn++;
        swap(x,y);
        e[nn].b=y;e[nn].nt=p[x];if(p[x]!=-1)e[p[x]].pre=nn;p[x]=nn;e[nn].a=x;e[nn].pre=-1;nn++;
    }

    void del(int i){
        if(e[i].pre!=-1)e[e[i].pre].nt=e[i].nt;
        if(e[i].nt!=-1)e[e[i].nt].pre=e[i].pre;
        if(i==p[e[i].a])p[e[i].a]=e[i].nt;
    }

    void add(int i){
        e[i].nt=p[e[i].a];
        if(p[e[i].a]!=-1)e[p[e[i].a]].pre=i;
        p[e[i].a]=i;
    }

    void build(int m){
        for(int i=1;i<=m;i++)p[i]=-1;
        for(int i=1;i<=m;i++){
            for(int j=i+1;j<=m;j++)anode(i,j);
        }
        if(m&1)return;
        for(int i=1;i<=m;i+=2){
            anode(i,i+1);
        }
    }

    int st[N*N],ans[N*N];

    void dfs(int x){
        st[++st[0]]=x;
        for(int i=p[x];i!=-1;i=e[i].nt){
            int t=e[i].b;
            del(i);
            del(i^1);
            dfs(t);
            break;
        }
    }

    void solve(){
        st[++st[0]]=1;
        while(st[0]){
            int u=st[st[0]--],flag=0;
            if(p[u]!=-1)dfs(u);
            else ans[++ans[0]]=u;
        }
    }

    int main(int argc, char* argv[]) {
    #ifdef WK
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
        scanf("%lld", &n);
        if(n==1){
            printf("1\n1");
            return 0;
        }
        ll l = 1, r = 1e9+5;
        ll res = 0;
        while (l <= r) {
            ll mid = l + r >> 1;
            if (cal1(mid * 2 + 1) > n) {
                r = mid - 1;
            } else {
                res = mid * 2 + 1;
                l = mid + 1;
            }
        }
        l = 1, r = 1e9+5;
        ll res1 = 0;
        while (l <= r) {
            ll mid = l + r >> 1;
            if (cal2(mid * 2) > n) {
                r = mid - 1;
            } else {
                res1 = mid * 2;
                l = mid + 1;
            }
        }
        res = max(res, res1);
        printf("%lld\n", res);
        if(n>2000000)return 0;
        
        build(res);
        solve();
        while(ans[0]<n)ans[++ans[0]]=1;
        for(int i=1;i<=n;i++){
            printf("%d%c",ans[i],(i==n)?'\n':' ');
        }
        return 0;
    }
    ```

## J. 邦邦的2-SAT模板

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    int main()
    {
        int n;
        scanf("%d", &n);
        if(n == 1) return 0 * puts("0");
        printf("%d\n", n);
        for(int i = 1; i < n; i ++) printf("%d %d\n", -i, i + 1);
        printf("%d %d\n", -n, -n);
        return 0;
    }
    ```

??? note "题目附录"
    ```cpp
    #include<cstdio>
    using namespace std;
    const int N=3010;
    int g[N<<1],nxt[N<<1],v[N<<1],num;
    int q[N<<1],t;
    bool vis[N<<1];
    int CNT;
    int n,m;
    void add(int x,int y){
        nxt[++num]=g[x];
        v[num]=y;
        g[x]=num;
    }
    bool dfs(int x){
        CNT++;
        if(vis[x>n?x-n:x+n])return 0;
        if(vis[x])return 1;
        vis[q[++t]=x]=1;
        for(int i=g[x];i;i=nxt[i])if(!dfs(v[i]))return 0;
        return 1;
    }
    bool solve(){
        for(int i=1;i<=n;i++)if(!vis[i]&&!vis[i+n]){
            t=0;
            if(!dfs(i)){
                while(t)vis[q[t--]]=0;
                if(!dfs(i+n))return 0;
            }
        }
        return 1;
    }
    int main()
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++)
        {
            int x,y;scanf("%d%d",&x,&y);
            if(x<0)x=n-x;if(y<0)y=n-y;
            add(x>n?x-n:x+n,y);add(y>n?y-n:y+n,x);
        }
        solve();
        return 0;
    }
    ```

## K. 破忒头的匿名信

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    const int maxn = 5e5 * 26;
    const int N = 5e5 + 10;

    int trie[maxn][26], cnt;
    int tag[maxn];
    int fail[maxn];
    int val[maxn], dep[maxn];

    void ins(char *s, int V)
    {
        int root =0;
        for(int i = 0; s[i]; i ++)
        {
            int id = s[i] - 'a', fa = root;
            if(!trie[root][id]) trie[root][id] = ++ cnt;
            root = trie[root][id];
            dep[root] = dep[fa] + 1; 
        }
        tag[root] = true;
        val[root] = min(val[root], V);
    }

    void build()
    {
        queue<int> que;
        for(int i = 0; i < 26; i ++) if(trie[0][i]) que.push(trie[0][i]);
        while(!que.empty())
        {
            int k = que.front();
            que.pop();
            for(int i = 0; i < 26; i ++)
            {
                if(trie[k][i])
                {
                    fail[trie[k][i]] = trie[fail[k]][i];
                    que.push(trie[k][i]);
                }else trie[k][i] = trie[fail[k]][i];
            }
        }
    }

    char s[maxn], t[maxn];
    ll dp[N];

    void query()
    {
        int u = 0, len = strlen(t + 1);
        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;
        for(int i = 1; i <= len; i ++)
        {
            u = trie[u][t[i] - 'a'];
            int en = u;
            while(en)
            {
                if(tag[en] && dp[i - dep[en]] != 0x3f3f3f3f) dp[i] = min(dp[i], dp[i - dep[en]] + val[en]);
                en = fail[en];
            }
        }
        if(dp[len] == 0x3f3f3f3f3f3f3f3f) dp[len] = -1;
        printf("%lld\n", dp[len]);
    }

    int main()
    {
        int n, x;
        scanf("%d", &n);
        memset(val, 0x3f, sizeof val);
        for(int i = 1; i <= n; i ++) 
        {
            scanf("%s%d", s, &x);
            ins(s, x);
        }
        build();
        scanf("%s", t + 1);
        query();
        return 0;
    }
    ```