#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define Hash unsigned long long

const int maxn=5010;
const Hash bit=10007;

int n,wmt,root,y[maxn*30],f[maxn*30];

char s[200];

struct node
{
	int next[26],son,depth;
	Hash hash;
	bool end;
}z[maxn*35];

bool cmp1(int a,int b)
{
	return z[a].depth<z[b].depth;
}

bool cmp2(int a,int b)
{
	if (z[a].son!=z[b].son) return z[a].son<z[b].son;
	else return z[a].hash<z[b].hash;
}

inline int newnode()
{
	wmt++;
	z[wmt].end=false;
	z[wmt].hash=0;
	z[wmt].depth=0;
	z[wmt].son=0;
	memset(z[wmt].next,0,sizeof(z[wmt].next));
	return wmt;
}

void insert()
{
	int l=strlen(s+1);
	int p=root;
	for (int a=1;a<=l;a++)
	{
		if (!z[p].next[s[a]-'a']) z[p].next[s[a]-'a']=newnode(),z[p].son++;
		p=z[p].next[s[a]-'a'];
	}
	z[p].end=true;
}

void dfs(int p)
{
	for (int a=0;a<26;a++)
		if (z[p].next[a]) dfs(z[p].next[a]),z[p].depth=max(z[p].depth,z[z[p].next[a]].depth);
	z[p].depth++;
}

int getf(int now)
{
	if (now==f[now]) return now;
	else return f[now]=getf(f[now]);
}

void Union(int p1,int p2)
{
	int f1=getf(p1);
	int f2=getf(p2);
	f[f1]=f2;
}

int main()
{
	scanf("%d",&n);
	wmt=0;
	root=newnode();
	for (int a=1;a<=n;a++)
	{
		scanf("%s",s+1);
		insert();
	}
	dfs(root);
	for (int a=1;a<=wmt;a++)
		y[a]=a;
	sort(y+1,y+wmt+1,cmp1);
	int ans=wmt;
	for (int a=1;a<=wmt;a++)
		f[a]=a;
	for (int a=1;a<=wmt;)
	{
		int b=a;
		while (b<=wmt && z[y[b]].depth==z[y[a]].depth)
			b++;
		b--;
		for (int c=a;c<=b;c++)
		{
			z[y[c]].hash=z[y[c]].end+1;
			for (int d=0;d<26;d++)
			{
				int p;
				if (z[y[c]].next[d]) p=getf(z[y[c]].next[d])+4;
				else p=3;
				z[y[c]].hash=z[y[c]].hash*bit+p;
			}
		}
		sort(y+a,y+b+1,cmp2);
		for (int c=a;c<=b;)
		{
			int d=c;
			while (d<=b && z[y[d]].son==z[y[c]].son && z[y[d]].hash==z[y[c]].hash)
				d++;
			d--;
			ans-=d-c;
			for (int e=c+1;e<=d;e++)
				Union(y[c],y[e]);
			c=d+1;
		}
		a=b+1;
	}
	printf("%d\n",ans);

	return 0;
}
