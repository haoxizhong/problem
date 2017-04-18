#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

double x[100010];

int main()
{
	int n;
	scanf("%d",&n);
	for (int a=1;a<=n;a++)
		scanf("%lf",&x[a]);
	double ans=0,sum=0;
	for (int a=1;a<=n;a++)
	{
		double f;
		scanf("%lf",&f);
		ans+=f*x[a];
		sum+=f;
	}
	printf("%.6lf\n",fabs(ans/sum));

	return 0;
}
