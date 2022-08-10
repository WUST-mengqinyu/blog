#include <cstdio>

typedef long long int int64;

const int Max_N = 200005;

int         len[Max_N * 2], ch[Max_N * 2][26], parent[Max_N * 2], fail[Max_N * 2], trans[Max_N * 2][26];
const char* cur[Max_N * 2];
int         scnt = 1, act = 1, r, ls = 1, ss = 1;

int Inf0 = 1 << 30, Inf1 = 1 << 30;

int   cnt;
int64 Ans;

void link(const int c, const int v) {
    parent[c] = v, ch[v][cur[c][len[v] + 1]] = c;
}

void extend_back(const char& c) {
    int last = 0;
    ++r;
    while (r && (r <= len[act] ? cur[act][r] != c : ch[act][c] == 0)) {
        if (r <= len[act]) {
            int split  = ++scnt;
            len[split] = r - 1, cur[split] = cur[act], fail[split] = 1;
            for (int _c = 0; _c != 26; ++_c) trans[split][_c] = trans[act][_c];
            link(split, parent[act]), link(act, split);
            act = split;
        }
        int n  = ++scnt;
        len[n] = --Inf0, cur[n] = &c - r;
        link(n, act);
        --r;
        ++cnt;
        if (last > 1)
            fail[last] = act, trans[act][cur[last][1]] = last;
        else if (ss > 1)
            trans[act][cur[ss][1]] = ss;
        if (ss > 1) trans[n][cur[ss][1]] = ss;
        last = act;
        ss   = n;
        if (act == 1)
            trans[1][cur[n][1]] = n;
        else {
            if (parent[act] == 1)
                trans[1][cur[last][1]] = last, act = 1;
            else
                act = fail[parent[act]];
            if (len[act] < r - 1)
                while (act = ch[act][(&c - r)[len[act] + 1]], len[act] < r - 1) trans[act][cur[last][1]] = last;
        }
    }
    if (last > 1) fail[last] = act, trans[act][cur[last][1]] = last;
    if (ls == 1) ls = ch[1][c];
    if (r > len[act]) act = ch[act][c];
    if (r == len[act]) trans[act][cur[ss][1]] = ss;
}

void extend_front(const char& c) {
    int p = ls, n;

    for (; p && !trans[p][c]; p = parent[p])
        ;
    if (p == 0)
        n = ++scnt, ++cnt, Ans += cnt + r;
    else if ((len[p] == r ? p : ch[p][cur[ls][len[p] + 1]]) == act && cur[ls][cnt] == c) {
        n = ss;
        if (n != ls) ss = trans[n][cur[ls][cnt - 1]], trans[n][cur[ls][cnt - 1]] = 0;
        ++r, Ans += cnt, ++Inf0, act = n;
    } else
        n = ++scnt, ++cnt, Ans += cnt + r - (len[p] + 1);
    len[n] = Inf1++, cur[n] = &c - 1;

    if (n != ls) {
        p = ls;
        for (; p && !trans[p][c]; p = parent[p]) trans[p][c] = n;
        if (trans[p][c] != n) {
            if (p == 0)
                link(n, 1);
            else {
                int t = trans[p][c];
                if (len[t] == len[p] + 1)
                    link(n, t);
                else {
                    int split  = ++scnt;
                    len[split] = len[p] + 1, fail[split] = p, cur[split] = cur[t];
                    for (int _c = 0; _c != 26; ++_c) trans[split][_c] = trans[t][_c];
                    link(split, parent[t]);
                    link(t, split), link(n, split);
                    for (; p && trans[p][c] == t; p = parent[p]) trans[p][c] = split;
                    if (act == t) {
                        if (r <= len[split]) act = split;
                        if (len[split] <= r) trans[split][cur[ss][1]] = ss;
                    }
                }
            }
        }
    }
    ls = n;
    if (ss == 1) ss = ls;
}

int   N, type;
int64 lastans;
char  op[15], c, s[Max_N * 2], *cur0 = s + Max_N, *cur1 = s + Max_N;

int main(int argc, char** argv) {
    scanf("%d %d", &N, &type);
    for (int i = 0; i != N; ++i) {
        scanf("%s %c", op, &c);
        c -= 'a';
        if (type) c = (c + lastans) % 26;
        if (op[5] == 'b')
            extend_back(*cur1++ = c), Ans += cnt;
        else
            extend_front(*--cur0 = c);
        printf("%lld\n", lastans = Ans);
    }

    return 0;
}