//用类似筛法的方法计算phi(1),phi(2),...,phi(n)
int phi[maxn];

void phi_table(int n)
{
    for (int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) if (!phi[i])
        for (int j = i; j <= n; j += i)
        {
            if (!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
}