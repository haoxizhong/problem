#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=110;

int n,q,e[maxn],s[maxn];

double dis[maxn][maxn],dist[maxn][maxn];

int main()
{
	int T=1;
	for (int t=1;t<=T;t++)
	{
		scanf("%d%d",&n,&q);
		for (int a=1;a<=n;a++)
			scanf("%d%d",&e[a],&s[a]);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
			{
				scanf("%lf",&dis[a][b]);
				if (dis[a][b]<0) dis[a][b]=1e+20;
				if (a==b) dis[a][b]=0;
			}
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				for (int c=1;c<=n;c++)
					dis[b][c]=min(dis[b][c],dis[b][a]+dis[a][c]);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				dist[a][b]=1e+20;
		for (int a=1;a<=n;a++)
			dist[a][a]=0;
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				if (dis[a][b]<=e[a]) dist[a][b]=dis[a][b]/s[a];
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				for (int c=1;c<=n;c++)
					dist[b][c]=min(dist[b][c],dist[b][a]+dist[a][c]);
		for (int a=1;a<=q;a++)
		{
			int s,e;
			scanf("%d%d",&s,&e);
			printf("%.6lf\n",dist[s][e]);
		}
	}

	return 0;
}
