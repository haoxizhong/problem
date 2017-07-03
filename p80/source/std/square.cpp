#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define inc(a,b) {a+=b;if (a>=mo) a-=mo;}
#define dec(a,b) {a-=b;if (a<0) a+=mo;}

const int maxk=2010;
const int mo=100000007;

int n,m,k,res1,res2,res3,res4,ans;

struct point
{
	int x,y;
	point(){}
	point(int a,int b)
	{
		x=a;y=b;
	}
	void init()
	{
		scanf("%d%d",&x,&y);
	}
	bool operator<(const point &a)const
	{
		if (x!=a.x) return x<a.x;
		else return y<a.y;
	}
	bool operator==(const point &a)const
	{
		return x==a.x && y==a.y;
	}
}p[maxk];

int pow(int a,int b)
{
	int ans=1;
	while (b)
	{
		if (b&1) ans=(long long)ans*a%mo;
		a=(long long)a*a%mo;
		b>>=1;
	}
	return ans;
}

int getv(int y,int x,int p)
{
	/*int ans=0;
	//printf("%d %d %d\n",x,y,p);
	for (int dx=0;dx<=min(x-p,y);dx++)
	{
		int l=0,r=min(y,p);
		r=min(r,dx+p);
		r=min(r,y-dx);
		//printf("%d %d %d\n",dx,l,r);
		ans+=(r-l+1);
	}
	//printf("\n");
	//int res=((long long)(min(x-p,y)+1)*(min(y,p)+1)-1)%mo;
	//printf("%d %d\n",ans-1,res);*/
	int res=0;
	int xm=min(x-p,y);
	if (y<=p) res=(long long)(y+y-xm+2)*(xm+1)/2%mo;
	else
	{
		if (y-xm>=p) res=(long long)(p+1)*(xm+1)%mo;
		else res=((long long)(p+1)*(y-p)+(long long)(p+y-xm+2)*(xm-y+p+1)/2)%mo;
	}
	//printf("%d %d\n",ans,res);
	return res-1;
}

void solve1(int x,int y)
{
	int delta=0;
	inc(delta,getv(x,m,y));
	inc(delta,getv(m-y,n,x));
	inc(delta,getv(n-x,m,y));
	inc(delta,getv(y,n,x));
	dec(delta,min(x,y));
	dec(delta,min(n-x,y));
	dec(delta,min(x,m-y));
	dec(delta,min(n-x,m-y));
	inc(res1,delta);
}

bool able(int x,int y)
{
	return x>=0 && y>=0 && x<=n && y<=m;
}

bool find(int x,int y)
{
	point pt=point(x,y);
	int l=0,r=k;
	while (l+1!=r)
	{
		int m=(l+r)>>1;
		if (p[m]<pt) l=m;
		else r=m;
	}
	return p[r]==pt;
}

void part1(int x1,int y1,int x2,int y2)
{
	int dx=x2-x1;
	int dy=y2-y1;
	int x3=x1+dx-dy,y3=y1+dx+dy;
	int x4=x1-dy,y4=y1+dx;
	if (able(x3,y3) && able(x4,y4))
	{
		inc(res2,1);
		int tx=find(x3,y3)+find(x4,y4);
		if (tx&1) inc(res3,1);
		if (tx==2) 
		{
			inc(res4,1);
			inc(res3,2);
		}
	}
}

void part2(int x1,int y1,int x2,int y2)
{
	x1<<=1;x2<<=1;y1<<=1;y2<<=1;
	int dx=(x2-x1)>>1;
	int dy=(y2-y1)>>1;
	int midx=x1+dx;
	int midy=y1+dy;
	int x3=midx-dy;
	int y3=midy+dx;
	int x4=midx+dy;
	int y4=midy-dx;
	if ((x3&1) || (x4&1) || (y3&1) || (y4&1)) return;
	x3>>=1;y3>>=1;x4>>=1;y4>>=1;
	if (able(x3,y3) && able(x4,y4))
	{
		inc(res2,1);
		int tx=find(x3,y3)+find(x4,y4);
		if (tx&1) inc(res3,1);
		if (tx==2) 
		{
			inc(res4,1);
			inc(res3,2);
		}
	}
}


void solve2(int x1,int y1,int x2,int y2)
{
	part1(x1,y1,x2,y2);
	part1(x2,y2,x1,y1);
	part2(x1,y1,x2,y2);
}

int main()
{
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);

	scanf("%d%d%d",&n,&m,&k);
	for (int a=1;a<=n && a<=m;a++)
		inc(ans,(long long)(n-a+1)*(m-a+1)*a%mo);
	for (int a=1;a<=k;a++)
		p[a].init();
	sort(p+1,p+k+1);
	for (int a=1;a<=k;a++)
		solve1(p[a].x,p[a].y);
	for (int a=1;a<=k;a++)
		for (int b=a+1;b<=k;b++)
			solve2(p[a].x,p[a].y,p[b].x,p[b].y);
	//printf("%d %d %d %d %d\n",ans,res1,res2,res3,res4);
	dec(ans,res1);
	inc(ans,res2);
	dec(ans,(long long)res3*pow(3,mo-2)%mo);
	inc(ans,(long long)res4*pow(6,mo-2)%mo);
	printf("%d\n",ans);

	return 0;
}
