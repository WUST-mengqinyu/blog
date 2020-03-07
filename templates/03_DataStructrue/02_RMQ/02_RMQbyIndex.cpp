//下标RMQ
int v[MAX],maxx[MAX][22],minn[MAX][22];
int pmax(int a,int b){return v[a]>v[b]?a:b;}
int pmin(int a,int b){return v[a]<v[b]?a:b;}
void RMQ(int n) {
	int i,j;
	for(i=1;i<=n;i++) {
		maxx[i][0]=minn[i][0]=i;
	}
	for(j=1;1<<(j-1)<=n;j++) {
		for(i=1;i+(1<<j)-1<=n;i++) {
			int t=1<<(j-1);
			maxx[i][j]=pmax(maxx[i][j-1],maxx[i+t][j-1]);
			minn[i][j]=pmin(minn[i][j-1],minn[i+t][j-1]);
		}
	}
}
int query(int l,int r) {
	int j=(int)(log10(r-l+1)/log10(2))+1;
	int i=r-(1<<(j-1))+1;
	return pmax(maxx[l][j-1],maxx[i][j-1]);
//	return pmin(minn[l][j-1],minn[i][j-1]);
}
