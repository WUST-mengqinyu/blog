## kmp算法

觉得自己字符串太菜了跟着算导重学一遍

### 算法简述

利用next数组线性的解决字符串匹配问题

定义原串`T[1...n]`，模式串`P（pattern）[1...m]`，若出现`T[s+1...s+m] = P[1...m]`则称此为一次成功的匹配，s称作有效偏移。

暴力复杂度是`O（n×m）`即对于原串的每个子串做一次循环的匹配。

### 算法实现

next数组：对于一个模式串`P`，它的前`i`项称作`P_i`，`next[i]`就表示最大的`next[i]`使得`P_{next[i]}`是`P_i`的后缀，定义`next[0]`为-1

例如串`ababaca`的next数组1到7项为：`0012301`

已知`P[1...q]`与`T[s+1...s+q]`匹配，而`P[q+1] != T[s+q+1]`，则将`T`后移一位的同时将`q`变为`next[q]`即可发现`P[1...next[q]]`与`T[s'+1, s'+k]`匹配（其中`s'+k = s+q`）。这样一来就可以`O(m)`预处理`O(n)`计算结果了。

getNext代码：

```cpp
int nex[maxm];

void getNext(char *s, int len) {
    int i = 0, j = -1;
    nex[i] = j;
    while(i < len) {
        if(j == -1 || s[i] == s[j]) nex[++i] = ++j;
        else j = nex[j];
    }
}
```

匹配代码：

```cpp
// a为原串，b为模式串，下标从0开始，找第一个出现模式串的位置，找不到返回-1
int KMP(char *a, char *b, int n, int m) {
    getNext(b, m);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || a[i] == b[j]) ++i, ++j;
        else j = nxt[j];
    }
    return j == m ? i - m + 1 : -1;
}
```

### 例题

（由于本文撰写时vjudge挂了，没有在vj上挂题）

[https://vjudge.net/contest/328570](https://vjudge.net/contest/328570)

#### [luoguP3375](https://www.luogu.org/problem/P3375)

题意：求出所有模式串的起始位置并输出next数组

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：test.cpp
*   创 建 者： badcw
*   创建日期： 9/22/19
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;

ll qp(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

template<class T>
inline bool scan(T &ret) {
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

// nxt[0]表示失配到完全不匹配
int nxt[maxn];

void getNext(char *s, int len) {
    int i = 0, j = -1;
    nxt[i] = j;
    while (i < len) {
        if (j == -1 || s[i] == s[j]) nxt[++i] = ++j;
        else j = nxt[j];
    }
}

// a为原串，b为模式串，下标从0开始，找第一个出现模式串的位置（起点为1），找不到返回-1
int KMP(char *a, char *b, int n, int m) {
    getNext(b, m);
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (j == -1 || a[i] == b[j]) ++i, ++j;
        else j = nxt[j];
        if (j == m) {
            printf("%d\n", i - m + 1);
            j = nxt[j];
        }
    }
    return j == m ? i - m + 1 : -1;
}

char s[maxn], p[maxn];

int main(int argc, char *argv[]) {
    scanf("%s%s", s, p);
    int lens = strlen(s), lenp = strlen(p);
    KMP(s, p, lens, lenp);
    for (int i = 1; i <= lenp; ++i) printf("%d%c", nxt[i], i == lenp ? '\n' : ' ');
    return 0;
}
```

#### A - Oulipo

题意：求p在s中出现的次数

题解：kmp扫扫扫`O(n)`

#### B - Number Sequence

题意：求p在s中第一次出现的下标

题解：kmp扫到第一次j=m停

#### C - Period

题意：给定s，求s的每个前缀的最小循环节使得任意个这样的循环节并行拼成这个前缀，其中前缀本身不算。

题解：kmp求最小循环节，`len - nxt[len]`就是该串的最小循环节大小。判一下能整除即是解。

#### D - Power Strings

题意：给定s求最大循环次数

题解：kmp求最小循环节

#### F - Cyclic Nacklace

题意：求最少补多少字符使原串成为循环串

题解：求出最小循环节然后随便写一下

#### G - Simpsons’ Hidden Talents

题意：给s和p串，求p串的前缀等于s的后缀的最大长度。

题解：求出p串的next数组，对着s跑一遍，到最后一个位置输出当前j即可。

#### H - Milking Grid

题意：给二维串s，求最小的左上角矩阵使得它是整个矩阵的一个循环节。

题解：行列互不影响，所以考虑单维的串即可。用hash将行或列处理成单个字符即可。最小值相乘就是答案。

#### I - Theme Section

题意：给串s求拆分形如XAXBX的最长X的长度

题解：nxt数组求出来后，首尾都是X即nxt从尾部往前跳，然后求出那段区间内中间有nxt与当前长度相等的点即是答案。

#### J - A Secret

题意：给s和p求p的所有后缀在s中出现的个数×p的后缀长度的和。

题解：首先对s和p都翻转，求s的每个前缀对p的前缀的最大匹配度，保存在后缀数组中，对后缀数组倒着往前线性扫一次就可以得出答案，因为后缀的i如果有匹配必能匹配到nxt[i]，所以加过去就可以了。此处后缀数组只是取它字面意思。

#### K - Bazinga

题意：给n个串，求最大下标满足前面的串有不是它的子串。

题解：由于如果s_i是s_{i+1}的子串，对s_{i+1}及以后的串都与s_i无关，所以做一个剪枝即可，最坏情况也只有`O(n*len)`