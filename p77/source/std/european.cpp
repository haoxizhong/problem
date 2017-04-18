#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

const int maxn=100010;
const long double eps=1e-6;

int n,hull[maxn],z[maxn],sum[maxn];

int sgn(long double x)
{
	if (fabsl(x)<=eps) return 0;
	if (x>0) return 1;
	else return -1;
}

struct point
{
	int id;
	long double x,y;
    bool operator<(const point &a)const
    {
        if (sgn(x-a.x)==0) return sgn(y-a.y)<0;
        else return sgn(x-a.x)<0;
    }
}p[maxn];
 
long double getdist(point a,point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
 
long double cross(point a,point b,point c)
{
    return (a.x-b.x)*(b.y-c.y)-(b.x-c.x)*(a.y-b.y);
}
 
bool cmp(point a,point b)
{
    return sgn(cross(p[1],a,b))>0;
}
 
bool tu(point a,point b,point c)
{
    long double v=cross(a,b,c);
    if (sgn(v)==0) return sgn(getdist(a,c)-getdist(b,c))>0;
    else return sgn(v)>0;
}

int main()
{
	scanf("%d",&n);
	for (int a=1;a<=n;a++)
	{
		scanf("%d",&z[a]);
		sum[a]=sum[a-1]+z[a];
		p[a].x=sum[a];p[a].y=sum[a];p[a].y/=z[a];p[a].id=a;
	}
	sort(p+1,p+n+1);
	sort(p+2,p+n+1,cmp);
	int num=0;
	for (int a=1;a<=n;a++)
	{
		while (num>=3 && tu(p[a],p[hull[num]],p[hull[num-1]]))
			num--;
		num++;
		hull[num]=a;
	}
	long double ans=0;
	for (int a=2;a<num;a++)
		ans+=fabsl(cross(p[hull[1]],p[hull[a]],p[hull[a+1]]));
	printf("%.5lf\n",(double)ans/2);

	return 0;
}
