| Name                                                         | Date      | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |
| ------------------------------------------------------------ | --------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| [The Preliminary Contest for ICPC Asia Shanghai 2019](https://www.jisuanke.com/contest/3003?view=challenges) | 2019/9/15 | 7/12   |  .   |  O   |  .   |  O   |  Ø   |  Ø   |  Ø   |  .   |  .   |  O   |  .   |  O   |



## tag

`#B sort（假线段树）# D 暴力 #　E 生成函数  #F dp # G暴力（unordermap hash） #J 背包 #L暴力`



## D. Counting Sequences I



## F. Rhyme scheme

 题意：给定一类字符串的构造方案：前i-1位的最大字符为'mx'，则第i位可以取的范围为['A','mx' + 1]。每组询问输出长度为n的串中字典序第k大的字符串。

题解：构造出的字符串方案数应该为贝尔数。根据题意，rhyme scheme可以形成一棵字典树，并且每个节点的子树大小取决于字典树路径上的最大字符。考虑dp求解某个子树对应的字符个数，令\(dp[i][j]\)表示在第i层，根节点到当前节点路径字符的最大值为j的子树大小，有dp方程`dp[i][j]=j*dp[i-1][j]+dp[i][j+1]`。询问时在字典树上从上往下走，假设根节点到当前节点路径上的最大值为mx，那么前mx个点的子树大小为`dp[n-dep][mx]`，最后一个节点的子树大小为`dp[n-dep][mx+1]`，不断往下走即可求出解。

```cpp
#include <bits/stdc++.h>

using namespace std;

__int128 dp[30][30], k;

template <class T>
inline bool scan(T &ret){
    char c;
    int sgn;
    if (c = getchar(), c == EOF) return 0; //EOF
    while (c != '-' && (c < '0' || c > '9')) c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9') ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

template <class T>
inline void out(T x) {
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');
}

int main()
{
    int T, n;
    scanf("%d", &T);
    for(int i = 0; i < 30; i ++) dp[0][i] = 1;
    for(int i = 1; i < 30; i ++)
        for(int j = 0; j < 30; j ++)
            dp[i][j] = dp[i - 1][j] * j + dp[i - 1][j + 1];
    for(int i = T - 1; i >= 0; i --)
    {
        for(int j = 1; j <= T - i; j ++)
        {
            out(dp[i][j]);
            printf(" ");
        }
        puts("");
    }

    for(int _ = 1; _ <= T; _ ++)
    {
        scanf("%d", &n); scan(k);
        printf("Case #%d: ", _);
        int c = 0, mx = 0;
        for(int i = 1; i <= n; i ++)
        {
            for(c = 0; c < mx && k > dp[n - i][mx]; c ++) k -= dp[n - i][mx];
            mx = max(c + 1, mx);
            printf("%c", 'A' + c);
        }
        puts("");
    }
}
```

## G. Substring

题意：给一个s串，给m个t串，分别求s串与每个t串乱序匹配的子串数量，乱序匹配指两串长度相等，首尾字符相等，中间重排之后相等即可。

题解：数据范围中t的总长不超过1e5，所以离线查询，对每种长度按窗口处理一次s，复杂度O（能过），乱序匹配用加法hash就可以了，这个范围甚至不会溢出longlong。唯一比较nb的点在于它的细节卡内存，unordermap只需要管那些t串满足的解，所以count先判断是否存在需要这个解，然后再加就可以了。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：G.cpp
*   创 建 者： badcw
*   创建日期： 9/17/19
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 50005;
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

#define ull ll
struct node {
    int len;
    int L, R, id;
    ull hash;
    bool operator < (const node& oth) const {
        return len < oth.len;
    }
}p[maxn];

string s, t;
int n;
int res[maxn];
unordered_map<ull, int> mp[26][26];

ull prime[] = {34183,13513,152993,13591,19687,350869,111187,766091,769297,633469,752273,298651,617191,880421,136067,1408397,726899,458921,2133701,2599847,2730947,4696343,10267237,18941059,34078909,69208409};

ull getHash() {
    ull tmp = 0;
    for (auto i : t) {
        tmp += prime[i - 'a'];
    }
    return tmp;
}

void cal(int len) {
    if (len > s.length()) return;
    ull tmp = 0;
    for (int i = 0; i < len; ++i) {
        tmp += prime[s[i] - 'a'];
    }
    if (mp[s[0] - 'a'][s[len - 1] - 'a'].count(tmp)) mp[s[0] - 'a'][s[len - 1] - 'a'][tmp] ++;
    for (int i = len; i < s.length(); ++i) {
        tmp += prime[s[i] - 'a'] - prime[s[i - len] - 'a'];
        if (mp[s[i - len + 1] - 'a'][s[i] - 'a'].count(tmp)) mp[s[i - len + 1] - 'a'][s[i] - 'a'][tmp] ++;
    }
}

int main(int argc, char* argv[]) {
    int T;
    cin >> T;
    int q;
    for (int kase = 1; kase <= T; ++kase) {
        cin >> s >> q;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) mp[i][j].clear();
        }
        for (int i = 1; i <= q; ++i) {
            cin >> t;
            p[i].hash = getHash();
            p[i].L = t[0] - 'a';
            p[i].R = t.back() - 'a';
            p[i].id = i;
            p[i].len = t.length();
            mp[p[i].L][p[i].R][p[i].hash] = 0;
        }
        sort(p + 1, p + 1 + q);
        int pre = 0;
        for (int i = 1; i <= q; ++i) {
            if (p[i].len != pre) cal(p[i].len), pre = p[i].len;
            res[p[i].id] = mp[p[i].L][p[i].R][p[i].hash];
        }
        for (int i = 1; i <= q; ++i) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
```





