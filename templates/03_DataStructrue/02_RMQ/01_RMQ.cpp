//一维RMQ
//MAX=1e6时 第二维开22 内存(int型)占10w
int v[MAX],maxx[MAX][22],minn[MAX][22];
void RMQ(int n)
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		maxx[i][0]=minn[i][0]=v[i];//下标rmq 初始化赋值成i
		for(j=1;1<<(j-1)<=n;j++)
		{
			maxx[i][j]=0;
			minn[i][j]=INF;
		}
	}
	for(j=1;1<<(j-1)<=n;j++)
	{
		for(i=1;i+(1<<j)-1<=n;i++)
		{
			int t=1<<(j-1);
			maxx[i][j]=max(maxx[i][j-1],maxx[i+t][j-1]);
			minn[i][j]=min(minn[i][j-1],minn[i+t][j-1]);
		}
	}
}
int query(int l,int r)
{
	int j=(int)(log10(r-l+1)/log10(2))+1;
	int i=r-(1<<(j-1))+1;
	return max(maxx[l][j-1],maxx[i][j-1]);
//	return min(minn[l][j-1],minn[i][j-1]);
}