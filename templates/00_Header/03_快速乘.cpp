//O(1)快速乘
ll mul(ll a, ll b, ll p)
{
    return (a * b - ll((long double)a * b / p) * p + p) % p;
}

//int128
ll ans = ((__int128) a * b) % p;

//O(log(n))
ll mul(ll a, ll b, ll p)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % p;
        a = (a << 1) % p;
        b >>= 1;
    }
    return res;
}