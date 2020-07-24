| Name                                                         | Date       | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |   L   |
| ------------------------------------------------------------ | ---------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [2020 Multi-University Training Contest 1](http://acm.hdu.edu.cn/search.php?field=problem&key=2020+Multi-University+Training+Contest+1&source=1&searchmode=source) | 2020/7/21 | 2/12   |  .   |  .   |  .   |  O   |  O   |  .   |  .   |  .   |  Ø   |  .   |  Ø   |  .   |


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
