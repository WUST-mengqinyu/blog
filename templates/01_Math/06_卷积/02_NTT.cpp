const int p = 998244353;
const int maxn = 3e6 + 10;

int n, m, limit = 1, l, r[maxn], G = 3, invG;
ll a[maxn], b[maxn];

ll qp(ll a, ll n = p - 2)
{
	ll ans = 1, base = a;
	for(; n; (base *= base) %= p, n >>= 1) if(n & 1) (ans *= base) %= p;
	return ans;
}

void NTT(ll *A, int type)
{
	for(int i = 0; i < limit; i ++)
		if(i < r[i]) swap(A[i], A[r[i]]);
	for(int mid = 1; mid < limit; mid <<= 1)
	{
		ll Wn = qp(type == 1 ? G : invG, (p - 1) / (mid << 1));
		for(int j = 0; j < limit; j += (mid << 1))
		{
			ll w = 1;
			for(int k = 0; k < mid; k ++ , w = w * Wn % p)
			{
				int x = A[j + k], y = w * A[j + k + mid] % p;
				A[j + k] = (x + y) % p;
				A[j + k + mid] = (x - y + p) % p;
			}
		}
	}
}

void mul()
{
	while(limit <= n + m) limit <<= 1, l ++;
	for(int i = 0; i < limit; i ++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	NTT(a, 1);
	NTT(b, 1);
	for(int i = 0; i < limit; i ++) a[i] = (a[i] * b[i]) % p;
	NTT(a, -1);
	ll inv = qp(limit, p - 2);
	for(int i = 0; i <= n + m; i ++) printf("%d ", a[i] * inv % p);
}