#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define wmt 1,n,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int maxn=100010;
const int maxk=10;

int n,m,col[maxn<<2|1];

struct rec
{
	int res[maxk];
	rec(){memset(res,0,sizeof(res));}
	rec operator+(const rec &b)const {
		rec z;
		int p1=0,p2=0;
		for (int a=0;a<maxk;a++)
			if (res[p1]>b.res[p2]) z.res[a]=res[p1++];
			else z.res[a]=b.res[p2++];
		return z;
	}
}z[maxn<<2|1];

void color(int rt,int c)
{
	col[rt]+=c;
	for (int a=0;a<maxk;a++)
		if (z[rt].res[a]) z[rt].res[a]+=c;
}

void push_col(int rt) {
	if (col[rt]) {
		color(rt<<1,col[rt]);
		color(rt<<1|1,col[rt]);
		col[rt]=0;
	}
}

void update(int rt) {
	z[rt]=z[rt<<1]+z[rt<<1|1];
}

void build(int l,int r,int rt)
{
	if (l==r) {
		scanf("%d",&z[rt].res[0]);
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	update(rt);
}

rec query(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l && r<=nowr) return z[rt];
	push_col(rt);
	int m=(l+r)>>1;
	if (nowl<=m)
	{
		if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
		else return query(lson,nowl,nowr);
	}
	else return query(rson,nowl,nowr);
}

void modify(int l,int r,int rt,int nowl,int nowr,int v)
{
	if (nowl<=l && r<=nowr)
	{
		color(rt,v);
		return;
	}
	push_col(rt);
	int m=(l+r)>>1;
	if (nowl<=m) modify(lson,nowl,nowr,v);
	if (m<nowr) modify(rson,nowl,nowr,v);
	update(rt);
}

int main()
{
	freopen("noname.in","r",stdin);
	freopen("noname.out","w",stdout);

	scanf("%d%d",&n,&m);
	build(wmt);
	for (int a=1;a<=m;a++)
	{
		int opt,l,r,v;
		scanf("%d%d%d%d",&opt,&l,&r,&v);
		if (opt==0) 
		{
			if (r-l+1<v) printf("-1\n");
			else printf("%d\n",query(wmt,l,r).res[v-1]);
		}
		else modify(wmt,l,r,v);
	}

	return 0;
}
