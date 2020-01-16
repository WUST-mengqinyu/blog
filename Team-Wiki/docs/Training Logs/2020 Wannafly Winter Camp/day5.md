## 上午讲课

来自分块爷 `nzhtl1477` 的三百页分块 ppt 把人都讲晕了

## 下午比赛

总之越打越菜，来自 dls 的迷惑题目

| Name                                                         |   Date    | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |
| ------------------------------------------------------------ | :-------: | :----: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 CCPC Wannafly Winter Camp Day5 (Div.1&2)](https://pintia.cn/problem-sets/1217641604302602240) | 2020/1/16 |  4/10  |  O   |  .   |  .   |  .   |  O   |  .   |  O  |  .   |  .  |  O  |

## To-do list

`G\J\I`

## A. Alternative Accounts

有至多三场比赛，n 个账号，一个人可能有多个账号，但是一个人在一场比赛中最多使用一个账号，求最少的人数

首先有 8 种账号，按照三场比赛来进行二进制压位，那么对于任意按位与为 0 的账号都可能属于同一个人，另外可以分析出如果 x 个账号属于同一个人，那么总量将减少 x - 1，所以对任意账号其实只要找出可行对能让它减少，本身并不带权，也就是说不存在优先性问题。所以考虑贪心的减掉所有的边即可。顺序先是减去内部三元环，再减去一对二的边，最后减去内部边即可完全减掉。

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    const int maxn = 1e5 + 10;
    int a[maxn], s[10];

    int main()
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for(int i = 0; i < k; i ++)
        {
            int t, x;
            scanf("%d", &t);
            while(t --)
            {
                scanf("%d", &x);
                a[x] |= (1 << i);
            }
        }
        for(int i = 1; i <= n; i ++) s[a[i]] ++;
        int res = n;
        res -= s[0];
        for(int i = 1; i <= 4; i *= 2)
        {
            int x = i, y = 7 ^ i;
            int tmp = min(s[x], s[y]);
            res -= tmp;
            s[x] -= tmp, s[y] -= tmp;
        }
        int tmp = min({s[1], s[2], s[4]});
        res -= 2 * tmp;
        s[1] -= tmp, s[2] -= tmp, s[4] -= tmp;
        for(int i = 1; i <= 4; i *= 2)
        {
            for(int j = i * 2; j <= 4; j *= 2)
            {
                int tmp = min(s[i], s[j]);
                res -= tmp;
                s[i] -= tmp, s[j] -= tmp;
            }
        }
        printf("%d\n", res);
        return 0;
    }
    ```

## E. Matching Problem

给 a，b 两个序列，b 序列长度为 4，求 a 的子序列有多少个满足和 b 的每个等于、不等关系一样

分类讨论即可，代码有点长

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=310;
    typedef long long LL;
    int n,m;
    int a[N],b[N];
    int hx[N],hy[N];
    map<int,int>mp;int tt;

    int findf(int x){
        int l=1,r=hy[0];
        while(l<=r){
            int mid=l+r>>1;
            if(hy[mid]>x)r=mid-1;
            else if(hy[mid]<x)l=mid+1;
            else return mid;
        }
    }

    LL cnt[N],sum[N],cnt2[N],cnt3[N];

    int judge(){
        for(int i=1;i<=4;i++)cnt[b[i]]++;
        LL mx=0;
        for(int i=1;i<=4;i++)mx=max(mx,cnt[i]);
        for(int i=1;i<=4;i++)cnt[i]=0;
        return mx;
    }

    void solve1(){
        for(int i=1;i<=n;i++)cnt[a[i]]++;
        LL ans=0;m=hy[0];
        for(int i=1;i<=m;i++)sum[i]=cnt[i]+sum[i-1];
        for(int i=1;i<=m;i++){
            for(int j=i+1;j<=m;j++){
                for(int k=j+1;k<=m;k++){
                    ans+=cnt[i]*cnt[j]*cnt[k]*(sum[m]-sum[k]);
                }
            }
        }
        printf("%lld\n",ans);
    }


    void solve2(){
        int idxa=-1,idxb=-1,mx=0,mf;m=hy[0];
        for(int i=1;i<=4;i++){
            cnt[b[i]]++;
            if(cnt[b[i]]>mx){
                mx=cnt[b[i]];mf=b[i];
            }
        }
        for(int i=1;i<=4;i++)cnt[b[i]]=0;
        for(int i=1;i<=4;i++){
            if(b[i]==mf)continue;
            if(idxa==-1)idxa=i;
            else idxb=i;
        }
        LL ans=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(a[i]!=a[j])continue;
                for(int k=1;k<=m;k++)cnt[k]=0;
                for(int k=1;k<=m;k++)cnt2[k]=0;
                if(idxb==idxa+1){
                    if(idxa==1){
                        for(int k=1;k<i;k++)if(a[k]!=a[i])cnt[a[k]]++;
                    }else if(idxa==2){
                        for(int k=i+1;k<j;k++)if(a[k]!=a[i])cnt[a[k]]++;
                    }else{
                        for(int k=j+1;k<=n;k++)if(a[k]!=a[i])cnt[a[k]]++;
                    }
                    if(b[idxa]==b[idxb]){
                        for(int k=1;k<=m;k++)if(k!=a[i])ans+=(cnt[k]+cnt2[k])*(cnt[k]+cnt2[k]-1)/2; 
                    }else{
                        LL sum1=0,sum2=0;
                        for(int k=1;k<=m;k++)if(k!=a[i])sum1+=cnt[k];
                        for(int k=1;k<=m;k++)if(k!=a[i])sum2+=(sum1-cnt[k])*cnt[k];
                        ans+=sum2/2;
                    }
                }else{
                    if(idxa==1){
                        for(int k=1;k<i;k++)if(a[k]!=a[i])cnt[a[k]]++;
                    }else if(idxa==2){
                        for(int k=i+1;k<j;k++)if(a[k]!=a[i])cnt[a[k]]++;
                    }
                    
                    if(idxb==3){
                        for(int k=i+1;k<j;k++)if(a[k]!=a[i])cnt2[a[k]]++;
                    }else if(idxb==4){
                        for(int k=j+1;k<=n;k++)if(a[k]!=a[i])cnt2[a[k]]++;
                    }
                    
                    if(b[idxa]==b[idxb]){
                        
                        for(int k=1;k<=m;k++){
                            if(k!=a[i])ans+=cnt[k]*cnt2[k];
                        }
                    }else{
                        LL sum1=0;
                        for(int k=1;k<=m;k++)if(k!=a[i])sum1+=cnt2[k];
                        
                        for(int k=1;k<=m;k++){
                            ans+=cnt[k]*(sum1-cnt2[k]);
                        }
                    }
                }
            }
        }
        printf("%lld\n",ans);
    }

    void solve3(){
        int idx=-1,mx=0,mf;m=hy[0];
        for(int i=1;i<=4;i++){
            cnt[b[i]]++;
            if(cnt[b[i]]>mx){
                mx=cnt[b[i]];mf=b[i];
            }
        }
        for(int i=1;i<=4;i++)cnt[b[i]]=0;
        for(int i=1;i<=4;i++){
            if(b[i]==mf)continue;
            idx=i;break;
        }
        LL ans=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(a[i]!=a[j])continue;
                LL sum1=i-1,sum2=j-i-1,sum3=n-j;
                for(int k=1;k<=m;k++)cnt[k]=cnt2[k]=cnt3[k]=0;
                
                for(int k=1;k<i;k++)cnt[a[k]]++;
                for(int k=i+1;k<j;k++)cnt2[a[k]]++;
                for(int k=j+1;k<=n;k++)cnt3[a[k]]++;
                
                //aaab
                if(idx==4)ans+=cnt[a[i]]*(sum3-cnt3[a[i]]);
                //aaba
                if(idx==3)ans+=cnt[a[i]]*(sum2-cnt2[a[i]]);
                //abaa
                if(idx==2)ans+=cnt3[a[i]]*(sum2-cnt2[a[i]]);
                //baaa
                if(idx==1)ans+=(sum1-cnt[a[i]])*cnt3[a[i]];
                
            }
        }
        printf("%lld\n",ans);
    }


    void solve4(){
        for(int i=1;i<=n;i++)cnt[a[i]]++;
        LL ans=0;m=hy[0];
        for(int i=1;i<=m;i++)if(cnt[a[i]]>=4)ans+=(cnt[a[i]]* (cnt[a[i]]-1) *(cnt[a[i]]-2)*(cnt[a[i]]-3) )/24;
        printf("%lld\n",ans);
    }

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
    #endif
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]),hx[++hx[0]]=a[i];
        for(int i=1;i<=4;i++){
            scanf("%d",&b[i]);
            if(!mp[b[i]])mp[b[i]]=++tt;
            b[i]=mp[b[i]];
        }
        
        sort(hx+1,hx+1+hx[0]);
        hy[++hy[0]]=hx[1];
        for(int i=2;i<=hx[0];i++)if(hx[i]!=hx[i-1])hy[++hy[0]]=hx[i];
        
        for(int i=1;i<=n;i++)a[i]=findf(a[i]);
        int st=judge();
        switch(st){
            case 1:solve1();return 0;
            case 2:solve2();return 0;
            case 3:solve3();return 0;
            case 4:solve4();return 0;
        }
        return 0;
    } 
    ```

## G. Cryptographically Secure Pseudorandom Number Generator

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int N=2000010;
    typedef long long LL;
    int n,m;LL p;
    LL inv[N];
    LL v[N],v2[N];

    int main(){
    #ifdef WK
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
        int T;scanf("%d",&T);
        while(T--){
            scanf("%lld",&p);
            LL mn=p+1;
            n=0;m=0;
            inv[1]=1;
            for(int i=2,sz=min(N,(int)p);i<sz;i++){
                inv[i]=(p-p/i)*inv[p%i]%p;
                if(inv[i]<mn){
                    n++;
                    v[n]=i;
                    v2[n]=inv[i];
                    mn=inv[i];
                    if(i>=mn)break;
                }
            }
            m=n;
            for(int i=m-2;i>=1;i--){
                n++;
                v[n]=v2[i];
                v2[n]=v[i];
            }
            printf("%d\n",n);
            for(int i=1;i<=n;i++)printf("%lld %lld\n",v[i],v2[i]);
        }
        return 0;
    } 
    ```

## J. Xor on Figures

??? note "Code"
    ```cpp
    #include <bits/stdc++.h>

    using namespace std;
    typedef long long ll;

    const int mod = 1e9 + 7;

    struct Base
    {
    #define TYPE bitset<1024>
        static const int len = 1024;
        bool rel; int sz;
        TYPE a[len];

        TYPE &operator[](int x) {
            return a[x];
        }

        TYPE operator[](int x) const {
            return a[x];
        }

        void insert(bitset<1024> t)
        {
            for(int i = len - 1; i >= 0; i --) 
            {
                if(!(t[i] == 1)) continue;
                if(a[i].count()) t ^= a[i];
                else 
                {
                    for(int j = 0; j < i; j ++) if(t[j]) t ^= a[j];
                    for(int j = i + 1; j < len; j ++) if(a[j][i] == 1) a[j] ^= t;
                    a[i] = t;
                    ++ sz;
                    return;
                }
            }
            rel = true;
        }
    }solve;

    ll qp(ll a, ll n)
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

    char s[50][50];

    int main()
    {
        int k;
        scanf("%d", &k);
        int n = 1 << k;
        for(int i = 0; i < n; i ++)
            scanf("%s", s[i]);
        for(int x = 0; x < n; x ++)
        {
            for(int y = 0; y < n; y ++)
            {
                bitset<1024> tmp;
                for(int i = 0; i < n; i ++)
                {
                    for(int j = 0; j < n; j ++)
                    {
                        int dx = (i + x) % n, dy = (j + y) % n;
                        int id = dx * n + dy;
                        if(s[i][j] == '1') tmp[id] = 1;
                    }
                }
                solve.insert(tmp);
            }
        }
        printf("%lld\n", qp(2, solve.sz));
        return 0;
    }
    ```