bool vis[(int)1e6+5];
int prim[(int)1e5], tot; // tot = 78499
void init() {
    for (int i = 2; i < 1e6+5; ++i) {
        if (vis[i]) continue;
        prim[++tot] = i;
        for (int j = i + i; j < 1e6+5; j += i) vis[j] = 1;
    }
}