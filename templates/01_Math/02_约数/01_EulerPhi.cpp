//计算欧拉phi函数，phi(n)且与n互素的正整数个数

int oula(int n){
    int rea=n;
    for(int i=2; i*i<=n; i++)
        if(n%i==0)//第一次找到的必为素因子
        {
            rea=rea-rea/i;
            do
                n/=i;//把该素因子全部约掉
            while(n%i==0);
        }
    if(n>1)
        rea=rea-rea/n;
    return rea;
} //单点欧拉 O(sqrt(n))

bool boo[50000];
int p[20000];
void prim(){
    memset(boo,0,sizeof(boo));
    boo[0]=boo[1]=1;
    int k=0;
    for(int i=2; i<50000; i++)
    {
        if(!boo[i])
            p[k++]=i;
        for(int j=0; j<k&&i*p[j]<50000; j++)
        {
            boo[i*p[j]=1;
            if(!(i%p[j]))
                break;
        }
    }
}//筛选法打表
int phi(int n)
{
    int rea=n;
    for(int i=0; p[i]*p[i]<=n; i++)//对于一些不是素数的可不遍历
        if(n%p[i]==0)
        {
            rea=rea-rea/n;
            do
                n/=p[i];
            while(n%p[i]==0);
        }
    if(n>1)
        rea=rea-rea/n;
    return rea;
} //素数+欧拉

int euler[maxn];
void init() {
    int i, j;
    for(i=1; i<maxn; i++)
        euler[i]=i;
    for(i=2; i<maxn; i+=2)
        euler[i]/=2;
    for(i=3; i<maxn; i+=2)
        if(euler[i]==i) {
            for(j=i; j<=maxn; j+=i)
                euler[j]=euler[j]/i*(i-1);
        }
} //递推欧拉表