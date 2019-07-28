const int maxn=1e6+10;

char a[maxn],b[maxn];
int nex[maxn];

void getNext()
{
    int n = strlen(b), i = 0, j = -1;
    nex[i] = j;
    while(i < n)
    {
        if(j == -1 || b[i] == b[j]) nex[++ i] = ++j;
        else j = nex[j];
    }
}

int KMP()
{
    int n = strlen(a), m = strlen(b);
    getNext(b);
    int i = 0, j = 0;
    while(i < n && j < m)
    {
        if(j == -1 || a[i] == b[j]) i ++, j ++;
        else j = nex[j];
    }
}