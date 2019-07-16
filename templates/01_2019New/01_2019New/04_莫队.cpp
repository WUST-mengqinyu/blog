#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 200005;

struct MO {
    int l, r, id;
}q[maxn];

int n, m, col[maxn], block, belong[maxn];
ll vis[maxn * 10], ans;
ll res[maxn];
bool cmp(const MO& a, const MO& b) { return belong[a.l] == belong[b.l] ? a.r < b.r : a.l < b.l; }
void add(ll x) {
    vis[x] ++;
    ans += x * (vis[x] * vis[x] - (vis[x] - 1) * (vis[x] - 1));
}

void del(ll x) {
    vis[x] --;
    ans -= x * ((vis[x] + 1) * (vis[x] + 1) - vis[x] * vis[x]);
}

int main() {
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &col[i]);
        belong[i] = i / block + 1;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while(r < q[i].r) add(col[++r]);
        while(r > q[i].r) del(col[r--]);
        while(l < q[i].l) del(col[l++]);
        while(l > q[i].l) add(col[--l]);
        res[q[i].id] = ans;
    }
    for (int i = 1; i <= m; ++i) printf("%lld\n", res[i]);
    return 0;
}
