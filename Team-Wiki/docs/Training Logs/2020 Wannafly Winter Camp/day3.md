## 早上讲课

专区 Div1，讲了些很 np 的图论我准备以后补一补，总之一个都不会

```
circle-square tree
弦图
点双联通
km
上下界费用流
最大流
最小割
竞赛图
完美消除序列
三（四）元环计数
gomory-hu tree
meet-in-middle
```

然后扯了很久的打比赛方法和队伍间方法，学到很多

我决定之后跟队友多 battle 签到速度请喝奶茶

## 下午比赛

| Name                                                         |   Date    | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |
| ------------------------------------------------------------ | :-------: | :----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 CCPC Wannafly Winter Camp Day3 (Div.1&2)](https://pintia.cn/problem-sets/1216926916261912576) | 2020/1/13 |  4/10  |  O   |  .   |  O   |  .   |  O   |  .   |  O   |  .   |  .   |  .   |

总之有点难顶，感觉题目画风突变，被数论题搞麻了，签完到每题做了，又不会反演就歇逼了。然后 rank 21，第一次出 20 名

## To-do list

`A\G`

## A. 黑色气球

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=2010;
    typedef long long LL;
    int n,m;
    int f[N][N];
    int a[N];
    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)scanf("%d",&f[i][j]);
        }
        if(n==2){
            printf("1 1");
            return 0;
        }
        for(int i=2;i<n;i++)a[i+1]=f[1][i+1]-f[1][i];
        int t=a[3],s=f[2][3];
        a[2]=(s-t)/2;a[1]=f[1][2]-a[2];
        for(int i=3;i<=n;i++)a[i]+=a[i-1];
        for(int i=1;i<=n;i++)printf("%d%c",a[i],(i==n)?'\n':' ');
        return 0;
    } 
    ```

## C. 无向图定向

给一张无向图，给每个点定向使得其成为一张有向无环图(DAG)，求最短的最长路径

我的做法是随机对点进行排序，然后将所有边按点大小排序，每次线性 dp 求出最大值，取其最小值即可

当然正解可以状压优化图的染色

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    const int maxn = 20;

    vector<int> G[maxn];
    int a[maxn];
    int n;
    int dp[maxn];

    int main()
    {
        int m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            u --, v --;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        if (n == 1) printf("0\n");
        else {
            for (int i = 0; i < n; ++i) a[i] = i;
            int res = m;
            for (int i = 0; i < 100000; ++i) {
                random_shuffle(a, a + n);
                for (int i = 0; i < n; ++i) dp[i] = 0;
                int now = 0;
                for (int i = 0; i < n; ++i) {
                    for (auto v : G[a[i]]) {
                        dp[v] = max(dp[v], dp[a[i]] + 1);
                        now = max(now, dp[v]);
                    }
                }
                res = min(res, now);
            }
            printf("%d\n", res - 1);
        }
        return 0;
    }
    ```

## E. 棋技哥

给出一个二位 01 矩阵，两人博弈每次选取一个黑块使得包含该黑块所有左上的点取反，没有黑块时当前选手失败，两人都想让先手获胜

其实分析一下发现怎么取胜负都是确定的，只需要从后往前把情况枚举一次即可

??? note "Code"
    ```cpp
    /*================================================================
    *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
    *
    *   创 建 者： badcw
    *   创建日期： 2020/1/14
    *
    ================================================================*/
    #include <bits/stdc++.h>

    #define ll long long
    using namespace std;

    const int maxn = 505;
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

    int n, m;
    char mp[maxn][maxn];

    int main(int argc, char* argv[]) {
        int T;
        scanf("%d", &T);
        for (int kase = 1; kase <= T; ++kase) {
            scanf("%d%d", &n, &m);
            for (int i = 1; i <= n; ++i) {
                scanf("%s", mp[i] + 1);
            }
            int flag = 0;
            int tmp = 0;
            for (int i = n; i >= 1; --i) {
                for (int j = m; j >= 1; --j) {
                    if (tmp % 2 == 1) {
                        mp[i][j] = mp[i][j] == '1' ? '0' : '1';
                    }
                    if (mp[i][j] == '1') {
                        flag++;
                        tmp++;
                    }
                }
            }
            if (tmp % 2 == 0) puts("aoligei");
            else puts("call");
        }
        return 0;
    }
    ```

## G. 火山哥周游世界

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=500010;
    typedef long long LL;
    int n,k;
    struct edge{
        int b,nt;LL w;
    }e[N*2];
    int p[N],nn;
    void anode(int x,int y,int z){
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;e[nn].w=z;
        swap(x,y);
        nn++;e[nn].b=y;e[nn].nt=p[x];p[x]=nn;e[nn].w=z;
    }

    LL d[N];int flag[N];
    LL ans[N];
    void dfs(int x,int fa=0){
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa)continue;
            dfs(t,x);
            if(flag[t]){
                d[x]=max(d[x],d[t]+e[i].w);
                flag[x]=1;
                ans[0]+=e[i].w*2;
            }
        }
    }

    void dfs2(int x,LL ex=0,LL fm=0,int fa=0){
        ans[x]=ex+ans[0]-max(fm,d[x]);
        LL mf=-1,mx=0,cmx=0,cmf=-1;
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa||!flag[t])continue;
            if(d[t]+e[i].w>mx){
                cmx=mx;cmf=mf;
                mx=d[t]+e[i].w;mf=t;
            }else if(d[t]+e[i].w>cmx){
                cmx=d[t]+e[i].w;cmf=t;
            }
        }
        
        for(int i=p[x];i;i=e[i].nt){
            int t=e[i].b;
            if(t==fa)continue;
            
            if(t==mf){
                LL tfm=max(fm,cmx)+e[i].w;
                dfs2(t,ex,tfm,x);
            }else{
                LL tfm=max(fm,mx)+e[i].w;
                if(!flag[t])dfs2(t,ex+2*e[i].w,tfm,x);
                else dfs2(t,ex,tfm,x);
            }
        }
        
    }

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d%d",&n,&k);
        for(int i=1;i<n;i++){
            int aa,bb,cc;
            scanf("%d%d%d",&aa,&bb,&cc);
            anode(aa,bb,cc);
        }
        for(int i=1;i<=k;i++){
            int aa;scanf("%d",&aa);
            flag[aa]=1;
        }
        dfs(1);
        dfs2(1);
        for(int i=1;i<=n;i++)printf("%lld\n",ans[i]);
        return 0;
    } 
    ```