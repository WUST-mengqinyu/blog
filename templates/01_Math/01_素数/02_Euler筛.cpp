const int maxn = 1e6 + 10;
int prime[maxn], v[maxn], n, cnt; 	//每个合数只会被它的最小质因子p筛一次

void Euler_Sieve()
{
	for(int i = 2; i <= n; i ++) 
	{
		if(!v[i]) v[i] = i, prime[++cnt] = i;
		for(int j = 1; j <= cnt && i * prime[j] <= n; j ++)
		{
			v[i * prime[j]] = prime[j];
			if(i % prime[j] == 0) break;
		}
	}
}