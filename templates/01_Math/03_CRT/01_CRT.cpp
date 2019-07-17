typedef long long ll;

void exgcd(ll a, ll b, ll &x, ll &y)
{
	if(b == 0) { x = 1; y = 0; return; }
	exgcd(b, a % b, x, y);
	ll t = x; x = y, y = t - a / b * y;
}

ll crt(ll *a, ll *m, int n)
{
	ll M = 1, ans = 0;
	for(int i = 1; i <= n; i ++) M *= m[i];
	for(int i = 1; i <= n; i ++) 
	{
		ll x = 0, y = 0;
		ll Mi = M / m[i];
		exgcd(Mi, m[i], x, y);
		ans = (ans + Mi % M * x % M * a[i] % M + M) % M;
	}
	if(ans < 0) ans += M;
	return ans;
}