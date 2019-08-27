const int maxn = 2e6 + 10;

int n, m, a, va, b, vb;
int low[maxn], dfn[maxn], color[maxn], cnt, scc_cnt;
bool instack[maxn];

vector<int> g[maxn];
stack<int> st;

void Tarjan(int u)
{
    low[u] = dfn[u] = ++cnt;
    st.push(u);
    instack[u] = true;
    for(const auto &v : g[u])
    {
        if(!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
        else if(instack[v]) low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u])
    {
        ++scc_cnt;
        do {
            color[u] = scc_cnt;
            u = st.top(); st.pop();
            instack[u] = false;
        } while(low[u] != dfn[u]);
    }
}

void TWO_SAT()
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++)
    {
        scanf("%d%d%d%d", &a, &va, &b, &vb);
        g[ a + n * (va & 1) ].push_back(b + n * (vb ^ 1));
        g[ b + n * (vb & 1) ].push_back(a + n * (va ^ 1));
    }
    cnt = scc_cnt = 0;
    for(int i = 1; i <= (n << 1); i ++) if(!dfn[i]) Tarjan(i);
}

void out()
{
    for(int i = 1; i <= n; i ++)
        if(color[i] == color[i + n]) { puts("IMPOSSIBLE"); return; }
    puts("POSSIBLE");
    for(int i = 1; i <= n; i ++)
        printf("%d ", color[i] < color[i + n]);
}