#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=1000010;
const int INF=0x3f3f3f3f;

int n,en,depth[maxn],q[maxn],f[maxn][2],s[maxn],g[2][3];

struct edge
{
	int e;
	edge *next;
}*v[maxn],ed[maxn<<1];

void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	scanf("%d",&n);
	for (int a=1;a<n;a++)
	{
		int s,e;
		scanf("%d%d",&s,&e);
		add_edge(s,e);
		add_edge(e,s);
	}
	int front=1,tail=1;
	depth[1]=1;
	q[1]=1;
	for (;front<=tail;)
	{
		int now=q[front++];
		for (edge *e=v[now];e;e=e->next)
			if (!depth[e->e])
			{
				depth[e->e]=depth[now]+1;
				q[++tail]=e->e;
			}
	}
	for (int a=n;a>=1;a--)
	{
		int now=q[a];
		int cnt=0;
		for (edge *e=v[now];e;e=e->next)
			if (depth[e->e]==depth[now]+1) s[++cnt]=e->e;
		if (cnt)
		{
			g[0][0]=f[s[1]][0]+1;
			g[0][1]=f[s[1]][1];
			g[0][2]=INF;
			int src=1,last=0;
			for (int b=2;b<=cnt;b++)
			{
				g[src][0]=g[last][0]+f[s[b]][0]+1;
				g[src][1]=min(g[last][0]+f[s[b]][1],g[last][1]+f[s[b]][0]+1);
				g[src][2]=min(g[last][1]+f[s[b]][1],g[last][2]+f[s[b]][0]+1);
				src^=1;last^=1;
			}
			f[now][1]=min(g[last][0],g[last][1]);
			f[now][0]=min(g[last][2],f[now][1]);
		}
	}
	printf("%d\n",2*f[1][0]+1);

	return 0;
}
