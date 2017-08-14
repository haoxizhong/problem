#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn=20;
const double eps=1e-5;

int n;

double t,m[maxn],x[maxn],v[maxn];

int sgn(double x)
{
	if (fabs(x)<=eps) return 0;
	if (x>0) return 1;
	else return -1;
}

bool knock(int a,int b)
{
	double deltax=x[a]-x[b];
	double deltav=v[a]-v[b];
	if (sgn(deltax)==sgn(deltav)) return false;
	{
		if (sgn(deltav)==0 || sgn(deltax)==0) return false;
		else return true;
	}
	return false;
}

double calc(int a,int b)
{
	double deltax=x[a]-x[b];
	double deltav=v[a]-v[b];
	return fabs(deltax/deltav);
}

void get(int a,int b)
{
	double v1=v[a],m1=m[a];
	double v2=v[b],m2=m[b];
	v[a]=((m1-m2)*v1+2*m2*v2)/(m1+m2);
	v[b]=((m2-m1)*v2+2*m1*v1)/(m1+m2);
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	scanf("%d%lf",&n,&t);
	for (int a=1;a<=n;a++)
		scanf("%lf%lf%lf",&x[a],&v[a],&m[a]);
	double nowt=0;
	while (true)
	{
		double happen=1e+20;
		int p1=0,p2=0;
		for (int a=1;a<=n;a++)
			for (int b=a+1;b<=n;b++)
				if (knock(a,b))
				{
					double delta=calc(a,b);
					if (sgn(nowt+delta-t)<=0 && sgn(happen-delta)>0)
					{
						happen=delta;
						p1=a;
						p2=b;
					}
				}
		if (p1)
		{
			for (int a=1;a<=n;a++)
				x[a]=x[a]+happen*v[a];
			nowt+=happen;
			get(p1,p2);
		}
		else
		{
			for (int a=1;a<=n;a++)
				x[a]=x[a]+(t-nowt)*v[a];
			break;
		}
	}
	for (int a=1;a<=n;a++)
		printf("%.3lf\n",x[a]);

	return 0;
}
