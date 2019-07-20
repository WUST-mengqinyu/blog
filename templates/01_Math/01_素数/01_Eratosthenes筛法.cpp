const int maxn = 1e6 + 10;
bool vis[maxn];
vector<int> prime;

void init()
{
	for(int i = 2; i < maxn; i ++) if(!vis[i])
		for(int j = i * i; j < maxn; j += i) vis[i] = true;
	for(int i = 2; i < maxn; i ++) if(!vis[i]) prime.push_back(i);
}