#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

int main()
{
	int test;
	scanf("%d",&test);
	for (;test--;)
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		if (x-1e-8<=y) printf("0.000000\n");
		else printf("%.6lf\n",log(x/y)+1);
	}

	return 0;
}
