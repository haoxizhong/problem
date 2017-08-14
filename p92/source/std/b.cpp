#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int n,m,k,z[1010][1010];

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			scanf("%d",&z[a][b]);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			z[a][b]+=z[a-1][b]+z[a][b-1]-z[a-1][b-1];
	for (int a=1;a<=k;a++)
	{
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		printf("%d\n",z[x2][y2]-z[x1-1][y2]-z[x2][y1-1]+z[x1-1][y1-1]);
	}

	return 0;
}
