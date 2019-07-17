const int maxn = 1e6 + 10;

char a[maxn], b[maxn];
int nex[maxn];

void getNext()
{
    int len = strlen(b), i = 0, j = -1;
    nex[i] = j;
    for (int i = 1; i < len; i++)
    {
        while (j != -1 && b[i + 1] != b[j]) j = nex[j];
        if (b[i] == b[j + 1]) j++;
        nex[i] = j;
    }
}

void KMP()
{
    int n = strlen(a), m = strlen(b);
    getNext();
    int j = -1;
    for (int i = 0; i < n; i++)
    {
        while (j != -1 && a[i] != b[j + 1]) j = nex[j];
        if (b[j + 1] == a[i]) j++;
    }
}