#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=100010;

int n,m,en,z[maxn*3],f[maxn][20],q[maxn],depth[maxn],sum[maxn*3][2],fd[maxn],start[maxn],end[maxn],value[maxn];

struct edge
{
	int e,d;
	edge *next;
}*v[maxn],ed[maxn<<1];

void add_edge(int s,int e,int d)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->d=d;
}

int get(int p,int d)
{
	if (d==-1) return p;
	int x=0;
	while (d)
	{
		if (d&1) p=f[p][x];
		d>>=1;
		x++;
	}
	return p;
}

int get_lca(int p1,int p2)
{
	if (depth[p1]<depth[p2]) swap(p1,p2);
	p1=get(p1,depth[p1]-depth[p2]);
	int x=0;
	while (p1!=p2)
	{
		if (!x || f[p1][x]!=f[p2][x])
		{
			p1=f[p1][x];
			p2=f[p2][x];
			x++;
		}
		else x--;
	}
	return p1;
}

int calc(int p1,int p2)
{
	if (p1==f[p2][0]) return value[1]-value[p2];
	else return value[p1]+fd[p1];
}

int calcp(int p,int v)
{
	int l=start[p]-1,r=end[p];
	while (l+1!=r)
	{
		int m=(l+r)>>1;
		if (v>z[m]) l=m;
		else r=m;
	}
	return r;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);

	scanf("%d%d",&n,&m);
	int tot=0;
	for (int a=1;a<n;a++)
	{
		int s,e,d;
		scanf("%d%d%d",&s,&e,&d);
		tot+=d;
		add_edge(s,e,d);
		add_edge(e,s,d);
	}
	depth[1]=1;
	int front=1,tail=1;
	q[1]=1;
	for (;front<=tail;)
	{
		int now=q[front++];
		for (edge *e=v[now];e;e=e->next)
			if (!depth[e->e])
			{
				depth[e->e]=depth[now]+1;
				fd[e->e]=e->d;
				f[e->e][0]=now;
				int p=now,x=0;
				while (f[p][x])
				{
					f[e->e][x+1]=f[p][x];
					p=f[p][x];
					x++;
				}
				q[++tail]=e->e;
			}
	}
	int cnt=0;
	for (int a=n;a>=1;a--)
	{
		int now=q[a];
		start[now]=cnt+1;
		for (edge *e=v[now];e;e=e->next)
			if (depth[e->e]==depth[now]+1)
			{
				z[++cnt]=value[e->e]+e->d;
				value[now]+=value[e->e]+e->d;
			}
		z[++cnt]=tot-value[now];
		end[now]=cnt;
		sort(z+start[now],z+end[now]+1);
		sum[end[now]][0]=z[end[now]];
		sum[end[now]][1]=0;
		for (int a=end[now]-1;a>=start[now];a--)
		{
			sum[a][0]=sum[a+1][0];
			sum[a][1]=sum[a+1][1];
			if ((a&1)==(end[now]&1)) sum[a][0]+=z[a];
			else sum[a][1]+=z[a];
		}
		cnt++;
	}
	for (int a=1;a<=m;a++)
	{
		int p1,p2;
		scanf("%d%d",&p1,&p2);
		int lca=get_lca(p1,p2);
		int dist=depth[p1]+depth[p2]-2*depth[lca];
		int delta=dist/2+(dist&1);
		int px,px1,px2;
		if (depth[p1]-depth[lca]<delta) px=get(p2,dist-delta);
		else px=get(p1,delta);
		if (depth[p1]-depth[lca]<delta-1) px1=get(p2,dist-delta+1);
		else px1=get(p1,delta-1);
		if (depth[p2]-depth[lca]<dist-delta-1) px2=get(p1,delta+1);
		else px2=get(p2,dist-delta-1);
		int ans=0;
		if (p1==px)
		{
			if (p2==px) ans=sum[start[px]][0];
			else
			{
				int v2=calc(px2,px);
				int p=calcp(px,v2);
				ans=sum[p+1][0]+sum[start[px]][1]-sum[p][1];
			}
		}
		else
		{
			if (p2==px)
			{
				int v1=calc(px1,px);
				int p=calcp(px,v1);
				ans=v1+sum[p+1][1]+sum[start[px]][0]-sum[p][0];
			}
			else
			{
				int v1=calc(px1,px);
				int pp1=calcp(px,v1);
				int v2=calc(px2,px);
				int pp2=calcp(px,v2);
				if (pp2==pp1) pp2++;
				if (pp1>pp2) swap(pp1,pp2);
				ans=v1+sum[pp2+1][dist&1]+sum[pp1+1][1-(dist&1)]-sum[pp2][1-(dist&1)]+sum[start[px]][dist&1]-sum[pp1][dist&1];
			}
		}
		printf("%d\n",ans);
	}

	return 0;
}
