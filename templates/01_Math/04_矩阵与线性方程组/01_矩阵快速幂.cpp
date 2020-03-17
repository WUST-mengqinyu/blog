const int mod = 1e9 + 7;
typedef long long ll;

int cur;
struct Matrix {ll a[105][105]; };

Matrix mul(Matrix a, Matrix b)
{
    Matrix res;
    memset(res.a, 0, sizeof res.a);
    for(int i = 0; i < cur; i++)
        for(int j = 0; j < cur; j++)
            for(int k = 0; k < cur; k++)
                (res.a[i][j] +=a.a[i][k] * b.a[k][j] % mod) %= mod;
    return res;
}

Matrix pow(Matrix a, ll n)
{
    Matrix ans, base = a;
    for(int i = 0; i < cur; i++) ans.a[i][i] = 1;
    while(n)
    {
        if(n & 1) ans = mul(ans, base);
        base = mul(base, base);
        n >>= 1;
    }
    return ans;
}