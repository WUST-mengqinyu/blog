// 代替gets
scanf("%[^\n]%*c", ss)

void out2(int x, int flag = 1) {
    if (x == 0) {
        if (flag) putchar('0');
        return;
    }
    out2(x >> 1, 0);
    putchar('0' + x % 2);
}