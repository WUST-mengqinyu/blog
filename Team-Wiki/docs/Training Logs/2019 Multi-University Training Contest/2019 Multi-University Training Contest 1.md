#2019 Multi-University Training Contest 1


| Date      | Solved | A    | B    | C    | D    | E    | F    | G    | H    | I    | J    | K    | L    | M    |
| --------- | ------ | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 2019/7/22 | 6/13   | Ø    | O    | .    | Ø    | O    | .    | .    | .    | Ø    | .    | .    | .    | Ø    |

## B. Operation

对每个点维护一个线性基，插入操作为继承上一个点的线性基并插入当前点的值。

维护每个基底组成的点g[i]，在未知L的情况下使查询LR尽可能大，考虑贪心，使组成线性基的点尽可能靠近当前点。

具体操作为，对于某一位的点g[i]，如果pos>g[i]，则把pos与g[i]交换，使pos成为线性基的基底。

对于每个询问，查询第R个线性基所有pos大于L的基底能组成的最大值。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e6 + 10;

int n;
inline int getpos(int x, int lasans) { return (x ^ lasans) % n + 1; }

struct LinearBasis
{
    int f[30], g[30];

    void ins(int x, int pos)
    {
        for(int i = 29; ~i; i --)
        {
            if((x >> i) & 1)
            {
                if(f[i])
                {
                    if(g[i] <= pos) { x ^= f[i]; f[i] ^= x; swap(g[i], pos); }
                    else x ^= f[i];
                }
                else { f[i] = x; g[i] = pos; break; }
            }
        }
    }

    int query(int l)
    {
        int res = 0;
        for(int i = 29; ~i; i --) if(g[i] >= l) res = max(res, res ^ f[i]);
        return res;
    }
}base[maxn];

int main()
{
    int t, q, op, l, r, x;
    scanf("%d", &t);
    while(t --)
    {
        scanf("%d%d", &n, &q);
        for(int i = 1; i <= n; i ++)
        {
            scanf("%d", &x);
            base[i] = base[i - 1];
            base[i].ins(x, i);
        }
        int ans = 0;
        while(q --)
        {
            scanf("%d", &op);
            if(op == 0)
            {
                scanf("%d%d", &l, &r);
                l = getpos(l, ans), r = getpos(r, ans);
                if(l > r) swap(l, r);
                printf("%d\n", ans = base[r].query(l));
            }
            else
            {
                scanf("%d", &x); n ++;
                base[n] = base[n - 1], base[n].ins(x ^ ans, n);
            }
        }
    }
    return 0;
}
```

## D. Vacation

考虑\(O(n)\)的解法。

对于某一辆车\(x\)，计算它到达距离停车线0点向右距离为\(\sum_{i=1}^x l_i​\)的时间，最大值即为答案。

*为什么*：因为如果某一辆车没有到达这个点，它后面的车肯定被它堵住了，也就导致0车不能到达停车线。所以每辆车都超过了它对应的这个位置的时间就是答案。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;
int l[maxn], s[maxn], v[maxn];

int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i <= n; i ++) scanf("%d", &l[i]);
        for(int i = 0; i <= n; i ++) scanf("%d", &s[i]);
        for(int i = 0; i <= n; i ++) scanf("%d", &v[i]);
        long long L = 0;
        double ans = 1.0 * s[0] / v[0], tm;
        for(int i = 1; i <= n; i ++)
        {
            L += l[i];
            tm = 1.0 * (L + s[i]) / v[i];
            ans = max(ans, tm);
        }
        printf("%f\n", ans);
    }
    return 0;
}
```

## E. Path

跑出最短路，取能够组成最短路的所有边，建新图求最小割。

### Code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 10000 + 10;
const int INF = 0x3f3f3f3f;

//用于表示边的结构体（终点，流量，反向边）
struct edges{int to, cap, rev; };

struct Dinic
{
	vector<edges> G[maxn];	//图的邻接表表示
	int level[maxn];	//顶点到源点的距离标号
	int iter[maxn];	//当前弧

	void init()
	{
	    for(int i = 1; i < maxn; i ++) G[i].clear();
	}
	
	void add(int from, int to, int cap)
	{
		G[from].push_back((edges){to, cap, G[to].size()});
		G[to].push_back((edges){from, 0, G[from].size() - 1});
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
				edges &e = G[v][i];
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
			edges &e = G[v][i];
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
}dinic;

struct Edge { int nex, to, tot, w; }edge[maxn];

struct Dijkstra
{
    int head[maxn], dis[maxn], cnt;

    void init()
    {
        memset(head, 0xff, sizeof head);
        cnt = 0;
    }

    void add(int u, int v, int w)
    {
        if(u == v) return;
        int p = -1;
        for(int i = head[u]; ~i; i = edge[i].nex) if(edge[i].to == v) { p = i; break; }
        if(~p)
        {
            if(w < edge[p].w) edge[p].w = w, edge[p].tot = 1;
            else if(w == edge[p].w) edge[p].tot ++;
            return;
        }
        edge[++cnt].nex = head[u];
        edge[cnt].w = w;
        edge[cnt].to = v;
        edge[cnt].tot = 1;
        head[u] = cnt;
    }

    void dijkstra(int s)
    {
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
        memset(dis, 0x3f, sizeof dis);
        que.push({0, s}); dis[s] = 0;
        while(!que.empty())
        {
            auto f = que.top(); que.pop();
            int u = f.second, d = f.first;
            if(d != dis[u]) continue;
            for(int i = head[u]; ~i; i = edge[i].nex)
            {
                int v = edge[i].to, w = edge[i].w;
                if(dis[u] + w < dis[v])
                {
                    dis[v] = dis[u] + w;
                    que.push({dis[v], v});
                    dinic.add(u, v, w * edge[i].tot);
                }
                else if(dis[u] + w == dis[v]) dinic.add(u, v, w * edge[i].tot);
            }
        }
    }
}G;

signed main()
{
    int t, n, m, u, v, w;
    scanf("%lld", &t);
    while(t --)
    {
        scanf("%lld%lld", &n, &m);
        G.init();
        dinic.init();
        while(m --)
        {
            scanf("%lld%lld%lld", &u, &v, &w);
            G.add(u, v, w);
        }
        G.dijkstra(1);
        printf("%lld\n", dinic.max_flow(1, n));
    }
    return 0;
}
```

## I. String

逐位构造答案，贪心地加入能够加入的字典序最小的字符（判断加入之后剩下的后缀中每种字符的数目是否满足条件）。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

char s[maxn], s1[maxn];
int cnt[maxn][26], l[26], r[26], used[26];
vector<int> g[26];

int main()
{
    int n, m;
    while(scanf("%s%d", s, &m) != EOF)
    {
        n = strlen(s);
        for(int i = 0; i < 26; i ++) scanf("%d%d", &l[i], &r[i]);
        memset(used, 0, sizeof used);
        memset(cnt, 0, sizeof cnt);
        for(int i = 0; i < 26; i ++) g[i].clear();
        for(int i = 0; i < n; i ++) g[s[i] - 'a'].push_back(i);
        for(int i = n - 1; i >= 0; i --)
            for(int j = 0; j < 26; j ++)
                cnt[i][j] = cnt[i + 1][j] + (s[i] == 'a' + j);
        vector<int>::iterator head[26];
        for(int i = 0; i < 26; i ++) head[i] = g[i].begin();

        int last = -1, now = 0;
        for(int i = 0; i < m; i ++)
        {
            for(int j = 0; j < 26; j ++)
            {
                if(used[j] == r[j]) continue;
                while(head[j] != g[j].end() && (*head[j]) <= last) head[j] ++;
                if(head[j] == g[j].end()) continue;

                bool flag = true;
                int sum = 0, pos = *head[j];
                used[j] ++;
                for(int k = 0; k < 26; k ++)
                {
                    if(cnt[pos + 1][k] + used[k] < l[k]) flag = false;
                    sum += max(l[k] - used[k], 0);
                }
                if(sum > m - i - 1) flag = false;
                sum = 0;
                for(int k = 0; k < 26; k ++)
                    sum += min(cnt[pos + 1][k], r[k] - used[k]);
                if(sum < m - i - 1) flag = false;

                if(!flag) used[j] --;
                else
                {
                    s1[i] = 'a' + j;
                    last = pos;
                    now ++;
                    break;
                }
            }
            if(now == i) break;
        }
        s1[m] = 0;
        if(now < m) printf("-1\n");
        else printf("%s\n", s1);
    }
    return 0;
}
```

