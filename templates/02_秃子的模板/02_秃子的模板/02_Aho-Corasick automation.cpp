const int maxn=5e5+10;

class AC_automatiion
{
public:
	int trie[maxn][26],cnt;
	int tag[maxn];
	int fail[maxn];

	void init()
	{
	    memset(trie,0,sizeof trie);
	    memset(tag,0,sizeof tag);
	    memset(fail,0,sizeof fail);
	    cnt=0;
	}

	void insert(char *str)
	{
		int root=0;
		for(int i=0;str[i];i++)
		{
			int id=str[i]-'a';
			if(!trie[root][id]) trie[root][id]=++cnt;
			root=trie[root][id];
		}
		tag[root]++;
	}

	void build()
	{
		queue<int> que;
		for(int i=0;i<26;i++) if(trie[0][i]) que.push(trie[0][i]);
		while(!que.empty())
		{
			int k=que.front(); que.pop();
			for(int i=0;i<26;i++)
			{
				if(trie[k][i]) {
					fail[trie[k][i]]=trie[fail[k]][i];
					que.push(trie[k][i]);
				}
				else trie[k][i]=trie[fail[k]][i];
			}
		}
	}

	int query(char *str)
	{
		int p=0,res=0;
		for(int i=0;str[i];i++)
		{
			p=trie[p][str[i]-'a'];
			for(int j=p;j&&~tag[j];j=fail[j]) res+=tag[j],tag[j]=-1;
		}
		return res;
	}
}AC;