// 适用于正负整数
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

void out2(int x, int flag = 1) {
    if (x == 0) {
        if (flag) putchar('0');
        return;
    }
    out2(x >> 1, 0);
    putchar('0' + x % 2);
}

inline int read() {
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

// 代替gets
scanf("%[^\n]%*c", ss)

// python一行读入
a,b = map(int, input().split())

a = []
for i in input().split():
    a.append(int(i))