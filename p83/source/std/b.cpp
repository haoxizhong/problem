#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int maxn=1000001;

int n,m,map[3][4],buff[3][4],rx,ry;

struct member
{
	int x[6],col;
	member()
	{
		for (int a=1;a<=5;a++)
			x[a]=0;
		col=0;
	}
	member operator+(const member &a)
	{
		member b;
		for (int c=1;c<=5;c++)
			b.x[c]=x[c]+a.x[c];
		return b;
	}
}node[maxn<<1|1],orz;

struct member2
{
	member now;
	int ans;
	member2()
	{
		ans=0;
	}
	member2(member a,int b)
	{
		now=a;
		ans=b;
	}
};

void update(int rt)
{
	for (int a=1;a<=5;a++)
		node[rt].x[a]=node[rt<<1].x[a]+node[rt<<1|1].x[a];
}

bool check(member now)
{
	memset(buff,0,sizeof(buff));
	int num=0;
	for (int a=1;a<=rx;a++)
	{
		num++;
		for (int b=1;b<=ry;b++)
			buff[a][b]+=now.x[num];
	}
	for (int a=1;a<=ry;a++)
	{
		num++;
		for (int b=1;b<=rx;b++)
			buff[b][a]+=now.x[num];
	}
	for (int a=1;a<=rx;a++)
		for (int b=1;b<=ry;b++)
			if (buff[a][b] % 2!=map[a][b]) return false;
	return true;
}

void push_col(int l,int r,int rt)
{
	if (node[rt].col)
	{
		int m=(l+r)>>1;
		node[rt<<1].col=node[rt<<1|1].col=node[rt].col;
		for (int a=1;a<=rx+ry;a++)
			node[rt<<1].x[a]=node[rt<<1|1].x[a]=0;
		node[rt<<1].x[node[rt].col]=m-l+1;
		node[rt<<1|1].x[node[rt].col]=r-m;
		node[rt].col=0;
	}
}

void change(int l,int r,int rt,int nowl,int nowr,int v)
{
	if ((nowl<=l) && (r<=nowr))
	{
		node[rt].col=v;
		for (int a=1;a<=rx+ry;a++)
			node[rt].x[a]=0;
		node[rt].x[v]=r-l+1;
		return;
	}
	push_col(l,r,rt);
	int m=(l+r)>>1;
	if (nowl<=m) change(lson,nowl,nowr,v);
	if (m<nowr) change(rson,nowl,nowr,v);
	update(rt);
}

member ask(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl>nowr) return orz;
	if ((nowl<=l) && (r<=nowr)) return node[rt];
	push_col(l,r,rt);
	int m=(l+r)>>1;
	member ans1,ans2;
	if (nowl<=m) ans1=ask(lson,nowl,nowr);
	if (m<nowr) ans2=ask(rson,nowl,nowr);
	return ans1+ans2;
}

member2 query(int l,int r,int rt,int nowl,int nowr,member now)
{
	if (node[rt].col)
	{
		int maxl=max(l,nowl);
		int minr=min(r,nowr);
		int ans=0;
		member oo;
		oo.x[node[rt].col]=1;
		member o;
		o=oo+now;
		if (check(o)) ans+=(minr-maxl+2)/2;
		o=o+oo;
		if (check(o)) ans+=(minr-maxl+1)/2;
		now=now+node[rt];
		member2 nowans=member2(now,ans);
		return nowans;
	}
	push_col(l,r,rt);
	int m=(l+r)>>1;
	member2 ans1,ans2;
	ans1=member2(now,0);
	if (nowl<=m) ans1=query(lson,nowl,nowr,now);
	if (m<nowr) ans2=query(rson,nowl,nowr,ans1.now);
	ans2.ans=ans2.ans+ans1.ans;
	return ans2;
}

int main()
{
	scanf("%d%d",&rx,&ry);
	for (int a=1;a<=rx;a++)
		for (int b=1;b<=ry;b++)
			scanf("%d",&map[a][b]);
	scanf("%d%d",&n,&m);
	node[1].col=1;
	node[1].x[1]=n;
	for (int a=1;a<=m;a++)
	{
		int t;
		scanf("%d",&t);
		switch(t)
		{
			case 0:
				{
					int d,x;
					scanf("%d%d",&d,&x);
					change(1,n,1,d,d,x);
					break;
				}
			case 1:
				{
					int l,r;
					scanf("%d%d",&l,&r);
					member now=ask(1,n,1,1,l-1);
					printf("%d\n",query(1,n,1,l,r,now).ans);
					break;
				}
			case 2:
				{
					int l,r,x;
					scanf("%d%d%d",&l,&r,&x);
					change(1,n,1,l,r,x);
					break;
				}
		}
	}
	return 0;
}

