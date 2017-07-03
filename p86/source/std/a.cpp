#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=210;

int n,m,w[maxn],v[maxn],f[maxn][maxn];

int main()
{
	scanf("%d%d",&n,&m);
	for (int a=1;a<=n;a++)
		scanf("%d%d",&w[a],&v[a]);
	for (int a=0;a<n;a++)
		for (int b=0;b<=m;b++)
		{
			f[a+1][b]=max(f[a+1][b],f[a][b]);
			if (b+w[a+1]<=m) f[a+1][b+w[a+1]]=max(f[a+1][b+w[a+1]],f[a][b]+v[a+1]);
			if (b+2*w[a+1]<=m) f[a+1][b+2*w[a+1]]=max(f[a+1][b+2*w[a+1]],f[a][b]+2*v[a+1]);
		}
	int ans=0;
	for (int a=0;a<=m;a++)
	   ans=max(ans,f[n][a]);
	printf("%d\n",ans);
	return 0;
}
