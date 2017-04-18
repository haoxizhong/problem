#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn=20;
const int maxt=500;

int n,k[maxn];

long double p[maxn],gua[maxn][maxt+10],ans[maxn];

int main()
{
	int test;
	scanf("%d",&test);
	for (;test--;)
	{
		scanf("%d",&n);
		for (int a=1;a<=n;a++)
		{
			double f;
			scanf("%d%lf",&k[a],&f);
			p[a]=f;
		}
		if (n==1) printf("1.000000\n");
		else
		{
			for (int a=1;a<=n;a++)
				gua[a][0]=0;
			for (int a=1;a<=n;a++)
				for (int b=1;b<=maxt;b++)
					gua[a][b]=powl(1-powl(p[a],b),k[a]);
			for (int a=1;a<=n;a++)
			{
				ans[a]=0;
				for (int b=1;b<=maxt;b++)
					for (int s=1;s<(1<<n);s++)
						if (!(s&(1<<(a-1))))
						{
							long double nowres=1-gua[a][b];
							for (int c=1;c<=n;c++)
							if (c!=a)
							{
								if (s&(1<<(c-1))) nowres = nowres * (gua[c][b]-gua[c][b-1]);
								else nowres = nowres * gua[c][b-1];
							}
							ans[a]+=nowres;
						}
			}
			for (int a=1;a<=n;a++)
			{
				printf("%.6lf",(double)ans[a]);
				if (a==n) printf("\n");
				else printf(" ");
			}
		}
	}

	return 0;
}
