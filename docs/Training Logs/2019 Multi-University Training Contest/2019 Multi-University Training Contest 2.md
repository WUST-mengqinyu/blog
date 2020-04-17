# 2019 Multi-University Training Contest 2

| Date      | Solved |  A   |  B   |  C   |  D   |  E   |  F   |  G   |  H   |  I   |  J   |  K   |  L   |
| --------- | ------ | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| 2019/7/24 | 6/12   |  .   |  .   |  .   |  .   |  O   |  .   |  .   |  Ø   |  Ø   |  O   |  Ø   |  Ø   |

## E. Everything Is Generated In Equal Probability

暴力跑出前两项，按题意模拟题目给的随机算法算出第3,4项，丢进OEIS找规律得到通项。

前5项分别是0,1/3,8/9,5/3,8/3，把分母通分成9之后的分子序列是0,3,8,15,24，那么通项就是$$F(i)=\frac{(i+1)(i-1)}{9}$$

### Code

#### Random

```cpp
#include <bits/stdc++.h>
#define random(a,b) ((a)+rand()%((b)-(a)+1))

using namespace std;

int ip(int a[], int len)
{
    int cnt = 0;
    for(int i = 0; i < len; i ++)
        for(int j = i + 1; j < len; j ++)
            if(a[i] > a[j]) cnt ++;
    return cnt;
}

int cal(int a[], int len)
{
    int cnt = 0;
    if(len > 0)
    {
        cnt = ip(a, len);
        int x = random(0, (1 <<(len + 1)) - 1);
        int tmp[10], len1 = 0;
        for(int i = 0; i < len; i ++) if((x >> i) & 1) tmp[len1 ++] = a[i];
        cnt += cal(tmp, len1);
    }
    return cnt;
}

int a[10], b[10];

int main()
{
    int tm = 90000;
    int n = 5;
    for(int i = 0; i < 10; i ++) a[i] = i + 1;
    long long cnt = 0;
    for(int i = 0; i < tm; i ++)
    {
        int len = random(1, n);
        for(int j = 0; j < len; j ++) b[j] = a[j];
        random_shuffle(b, b + len);
        cnt += cal(b, len);
    }
    printf("%lld\n", cnt);
    return 0;
}
```

#### Solution

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int mod = 998244353;

ll inv(ll a, ll n = mod - 2)
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

int main()
{
    long long n;
    while(scanf("%lld", &n) != EOF)
        printf("%lld\n", (n + 1) * (n - 1) % mod * inv(9) % mod);
    return 0;
}
```

## H. Harmonious Army

 出了一万遍的最小割模型，然而比赛的时候看都没看这题。

大概BZOJ2127，BZOJ2132，BZOJ3894都是这个模型的题。

![pic](https://images2015.cnblogs.com/blog/790791/201603/790791-20160322161742151-1423086674.png)

对这个模型建像上图这样的网络流，我们令\(S=A+B+C\)表示三种收益的和，图上每一种割法表示减去一部分的收益，假设当前割集之和为\(X\)，我们需要构造网络使S-割集=当前选法的收益，这个时候的最小割即为所求解。

割集为{a,b}时表示两人选的都是Mages，收益为C，需要减去的收益为\(S-C=A+B\)，有\(a+b=A+B\)

割集为{c,d}时表示两人选的都是Warriors，收益为A，需要减去的收益为\(S-A=B+C\)，有\(c+d=B+C\)

割集为{a,e,d}或者{b,e,c}时表示一个人选Mage，另一个人选Warrior，收益为B，需要减去的收益为\(S-B=A+C\)，有\(a+e+d=A+C\),\(b+e+c=A+C\)

不妨令a=b,c=d,可以得到一组解\(a=b=(A+B)/2\)，\(c=d=(C+D)/2\)，\(e=-B+(A+C)/2\)

对于每一组(x,y)建这样的网络跑最小割，用总收益减去最小割即为所求解。

为了避免建图过程中出现小数可以把所有权值x2，输出时再/2

### Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;


const int MAX_V = 1000 + 10;
const int INF = 0x3f3f3f3f3f3f3f3f;

struct Dinic
{
	//用于表示边的结构体（终点，流量，反向边）
	struct edge{int to, cap, rev;};

	vector<edge> G[MAX_V];	//图的邻接表表示
	int level[MAX_V];	//顶点到源点的距离标号
	int iter[MAX_V];	//当前弧

	void init(int n)
	{
		for(int i = 0; i <= n; i ++) G[i].clear();
	}

	void add(int from, int to, int cap)
	{
		G[from].push_back((edge){to, cap, G[to].size()});
		G[to].push_back((edge){from, 0, G[from].size() - 1});
	}

	//计算从源点出发的距离标号
	void bfs(int s)
	{
		memset(level, -1, sizeof(level));
		queue<int> que;
		level[s] = 0;
		que.push(s);
		while(!que.empty())
		{
			int v = que.front(); que.pop();
			for(int i = 0; i < G[v].size(); i++)
			{
				edge &e = G[v][i];
				if(e.cap > 0 && level[e.to] < 0)
				{
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}

	//通过DFS寻找增广路
	int dfs(int v, int t, int f)
	{
		if(v == t) return f;
		for(int &i = iter[v]; i<G[v].size(); i++)
		{
			edge &e = G[v][i];
			if(e.cap > 0 && level[v] < level[e.to])
			{
				int d = dfs(e.to, t, min(f, e.cap));
				if(d > 0)
				{
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	//求解从s到t的最大流
	int max_flow(int s, int t)
	{
		int flow = 0;
		for(;;)
		{
			bfs(s);
			if(level[t] < 0) return flow;
			memset(iter, 0, sizeof(iter));
			int f;
			while((f = dfs(s,t,INF)) > 0) flow += f;
		}
	}
}ans;

int w1[510], w2[510];

signed main()
{
    int n, m, u, v, a, b, c;
    while(scanf("%lld%lld", &n, &m) != EOF)
    {
        int S = 0, T = n + 1;
        ans.init(T);
        for(int i = 0; i <= T; i ++) w1[i] = w2[i] = 0;
        int res = 0;
        while(m --)
        {
            scanf("%lld%lld%lld%lld%lld", &u, &v, &a, &b, &c);
            res += 2 * (a + b + c);
            w1[u] += a + b;
            w1[v] += a + b;
            w2[u] += b + c;
            w2[v] += b + c;
            ans.add(u, v, a + c - 2 * b);
            ans.add(v, u, a + c - 2 * b);
        }
        for(int i = 1; i <= n; i ++)
        {
            ans.add(S, i, w1[i]);
            ans.add(i, T, w2[i]);
        }
        res -= ans.max_flow(S, T);
        res /= 2;
        printf("%lld\n", res);
    }
    return 0;
}
```


## I. [I Love Palindrome String](https://cn.vjudge.net/contest/314097#problem/I)

题意：求所有长度为1～n的子串满足\(S_i^j\)和\(S_i^{(i+j)/2}\)为回文串的个数

题解：对所有回文串来说，它前半段是否是回文串都是确定是，所以回文树维护所有本质不同串，每增加一个节点就计算这个节点的前半段是否是回文串，可以直接上一手hash快速判断，然后如果是，该本质串的长度就要加个它个数的权值，最后整合起来即可，复杂度\(O(n)\)。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1009.cpp
*   创 建 者： badcw
*   创建日期： 19-7-25
*
================================================================*/
#include <bits/stdc++.h>
 
#define ll long long
using namespace std;
 
const int maxn = 3e5 + 5;
const int mod = 51123987;
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

typedef unsigned long long ull;
struct mhash {
    ull base[maxn];
    ull hash_index[maxn];
    ull seed; //31, 131
    void inithash(ull seedt = 31) {
        base[0] = 1;
        seed = seedt;
        for (int i = 1; i < maxn; ++i) base[i] = base[i - 1] * seed;
    }
    void hash(char *p, int n) { // from 1 to n
        hash_index[0] = 0;
        for (int i = 1; i <= n; ++i) hash_index[i] = hash_index[i - 1] * seed + p[i] - 'a';
    }
    ull gethash(int s, int e) {
        return hash_index[e] - hash_index[s - 1] * base[e - s + 1];
    }
}pre, last;

int n;
char s[maxn];
char s1[maxn];

bool check(int l, int r) {
    return pre.gethash(l, r) == last.gethash(n - r + 1, n - l + 1) &&
        pre.gethash(l, (l + r) / 2) == last.gethash(n - (l + r) / 2 + 1, n - l + 1);
}

const int N = 26;

struct Palindromic_Tree {
//    vector<pair<int, int> > next[maxn];
    int ok[maxn];
    int next[maxn][N];//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
    int fail[maxn]{};//fail指针，失配后跳转到fail指针指向的节点
    int cnt[maxn]{}; //表示节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
    int num[maxn]{}; //表示以节点i表示的最长回文串的最右端点为回文串结尾的回文串个数
    int len[maxn]{};//len[i]表示节点i表示的回文串的长度（一个节点表示一个回文串）
    int S[maxn]{};//存放添加的字符
    int last{};//指向新添加一个字母后所形成的最长回文串表示的节点。
    int n{};//表示添加的字符个数。
    int p{};//表示添加的节点个数。

    int newnode(int l) {//新建节点
//        next[p].clear();
        for (int i = 0; i < N; ++i) next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = l;
        return p++;
    }

    void init() {//初始化
        n = last = p = 0;
        newnode(0);
        newnode(-1);
        S[n] = -1;//开头放一个字符集中没有的字符，减少特判
        fail[0] = 1;
    }

    int get_fail(int x) {//和KMP一样，失配后找一个尽量最长的
        while (S[n - len[x] - 1] != S[n]) x = fail[x];
        return x;
    }

    int add(int c, int pos) {
        S[++n] = c;
        int cur = get_fail(last);//通过上一个回文串找这个回文串的匹配位置
//        int x = find(cur, c);
//        if (!x) {
        if (!next[cur][c]) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
            int now = newnode(len[cur] + 2);//新建节点
//            x = now;
//            fail[now] = find(get_fail(fail[cur]), c);
//            next[cur].emplace_back(make_pair(c, now));
            fail[now] = next[get_fail(fail[cur])][c];//和AC自动机一样建立fail指针，以便失配后跳转
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
            ok[now] = check(pos - len[now] + 1, pos);
        }
//        last = x;
        last = next[cur][c];
        cnt[last]++;
        return num[last];
    }

    void count() {
        for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
        //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
    }
} solve;

int ttans[maxn];

int main(int argc, char* argv[]) {
    pre.inithash();
    last.inithash();
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) s1[n - i + 1] = s[i];
        pre.hash(s, n);
        last.hash(s1, n);
        solve.init();
        for (int i = 1; i <= n; ++i) solve.add(s[i] - 'a', i);
        solve.count();
        for (int i = 1; i <= n; ++i) ttans[i] = 0;
        for (int i = 2; i <= solve.p; ++i) {
            ttans[solve.len[i]] += solve.cnt[i] * solve.ok[i];
        }
        for (int i = 1; i <= n; ++i) printf("%d%c", ttans[i], i == n ? '\n' : ' ');
    }
    return 0;
}
```



## J. [Just Skip The Problem](https://cn.vjudge.net/problem/HDU-6600)

 题意：要确定一个2进制位为n的数x，求最少需要多少次询问，每次询问可以回答它&x是否为0。问所有的最少次数的方案数。

题解：推一推显然每次问它某个2进制位就行，最少n次，然后就是n个数的全排列，由于模数只有`1e6+3`，直接推前`1e6+3`项的阶乘，后面全是0即可。

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：J.cpp
*   创 建 者： badcw
*   创建日期： 19-7-25
*
================================================================*/
#include <bits/stdc++.h>

#define ll long long
using namespace std;

const int maxn = 1e6+4;
const int mod = 1e6+3;
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

ll jie[maxn] = {1};

int main(int argc, char* argv[]) {
    for (int i = 1; i < maxn; ++i) jie[i] = jie[i - 1] * i % mod;
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%lld\n", n < maxn ? jie[n] : 0ll);
    }
    return 0;
}
```



## K. [Keen On Everything But Triangle](https://cn.vjudge.net/problem/HDU-6601)

 题意：给一个序列，求l到r中使用三个数字能组成的三角形中的最长周长。

题解：首先了解到这三条边必然是（数值大小上）相邻的三个。反证法易证，就直接是一定有更相邻的数可以使得答案更大，然后考虑从小到大不合法的方案，显然`1 1 2 3 5 8 ...`这个序列是最小的能构不成三角形的序列，而我们都知道斐波那契数列递增巨快，推出来大概44项就超过1e9了，然后就维护区间前44项大值即可。本来写了一波巨优美的线段树+莫队，然后就暴毙在莫队的根号复杂度下了。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1011.cpp
*   创 建 者： badcw
*   创建日期： 19-7-24
*
================================================================*/
#include <bits/stdc++.h>
 
#define ll long long
using namespace std;
 
const int maxn = 1e5+5;
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

int val[maxn<<2][45];
int a[maxn];
int res[45], tp[45];
int le, re, k;
int n, m;

inline void pushup(int *a, int *b) {
    int i = 0, j = 0, now = 0;
    while (now < 45) {
        if (a[i] > b[j]) {
            res[now++] = a[i++];
        } else res[now++] = b[j++];
    }
}

inline void build(int rt, int l, int r) {
    if (l == r) {
        val[rt][0] = a[l];
        for (int i = 1; i < 45; ++i) val[rt][i] = 0;
        return;
    }
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(val[rt << 1], val[rt << 1 | 1]);
    for (int i = 0; i < 45; ++i) val[rt][i] = res[i];
}

inline void query(int rt, int l, int r) {
    if (le <= l && r <= re) {
        pushup(tp, val[rt]);
        for (int i = 0; i < 45; ++i) tp[i] = res[i];
        return;
    }
    int mid = l + r >> 1;
    if (le <= mid) query(rt << 1, l, mid);
    if (re > mid) query(rt << 1 | 1, mid + 1, r);
}

int main(int argc, char* argv[]) {
//    freopen("data1.in", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        build(1, 1, n);
        while (m--) {
            scanf("%d%d", &le, &re);
            for (int i = 0; i < 45; ++i) tp[i] = 0;
            query(1, 1, n);
            ll tt = -1;
            for (int i = 0; i < 43; ++i) {
                if (tp[i + 2] == 0) break;
                if (tp[i + 1] + tp[i + 2] > tp[i]) {
                    tt = (ll)tp[i] + tp[i + 1] + tp[i + 2];
                    break;
                }
            }
            printf("%lld\n", tt);
//            fflush(stdout);
        }
    }
    return 0;
}
```



## L. [Longest Subarray](https://cn.vjudge.net/contest/314097#problem/L)
题意：给nck，表示序列长度为n，序列中元素集为c，要求最长的子序列使得序列中所有的元素个数要么是0要么不小于k。

题解：这也太容易去想dp解法了吧，然后发现复杂度能上天，c维dp。然后考虑维护对每个右端点每个数的能用的区间，显然除了右端点当前的值，其他值的区间与上一个右端点相同，多一个在当前区间能取，所以考虑线段树维护每个点能取多少个值，当前点首先加上c-1个值，然后考虑当前值的区间变化，一个是0区间被去掉了，所以从当前点值的上一个到当前点-1区间-1，再一个是当前点的前k个多了一个，所以从k-1到k区间+1，然后找最左边值为c的点与当前点作差更新答案，这个操作常用于线段树，实际上和单点查询一个复杂度。就是优先左儿子，如果左儿子有解直接返回结果，否则返回右儿子，实际上我维护最大值之后它有没有解很容易。这个题最好是维护一下每个点在哪出现，然后第一个出现的地方直接设为0，否则有点难以处理边界，我re了一面。

代码：

```cpp
/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：1012.cpp
*   创 建 者： badcw
*   创建日期： 19-7-24
*
================================================================*/
#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")

#define ll long long
using namespace std;

const int maxn = 1e5+5;
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

ll val[maxn<<2], lazy[maxn<<2];
int le, re;
vector<int> pos[maxn];
ll k;
int n, m, C;

inline void pushdown(int rt) {
    if (lazy[rt]) {
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        val[rt << 1] += lazy[rt];
        val[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}

inline void build(int rt, int l, int r) {
    val[rt] = lazy[rt] = 0;
    if (l == r) return;
    int mid = l + r >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
}

inline void update(int rt, int l, int r) {
    if (re < le || le <= 0) return;
    if (le <= l && r <= re) {
        val[rt] += k;
        lazy[rt] += k;
        return;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    if (le <= mid) update(rt << 1, l, mid);
    if (re > mid) update(rt << 1 | 1, mid + 1, r);
    val[rt] = max(val[rt << 1], val[rt << 1 | 1]);
}

inline int query(int rt, int l, int r) {
    if (val[rt] < C) return -1;
    if (l == r) {
        return l;
    }
    pushdown(rt);
    int mid = l + r >> 1;
    int res = query(rt << 1, l, mid);
    if (res != -1) return res;
    return query(rt << 1 | 1, mid + 1, r);
}

int main() {
    while (scanf("%d%d%d", &n, &C, &m) != EOF) {
        for (int i = 1; i <= C; ++i) {
            pos[i].clear();
        }
        build(1, 1, n);
        int res = 0;
        for (int i = 1, x; i <= n; ++i) {
            scanf("%d", &x);
            le = re = i;
            k = C - 1;
            update(1, 1, n);
            if (pos[x].size()) le = pos[x].back() + 1;
            else le = 1;
            re = i - 1;
            k = -1;
            if (le <= re) update(1, 1, n);
            pos[x].push_back(i);
            int p = pos[x].size() - m - 1;
            if (p >= 0) {
                le = pos[x][p] + 1;
                re = pos[x][p + 1];
                k = 1;
                update(1, 1, n);
            } else if (p == -1 && !pos[x].empty()) {
                le = 1;
                re = pos[x][0];
                k = 1;
                update(1, 1, n);
            }
            int tmp = query(1, 1, n);
            if (tmp != -1) res = max(res, i - tmp + 1);
        }
        printf("%d\n", res);
    }
    return 0;
}
```

