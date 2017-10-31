#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=310;

int n,m,res[maxn],ans[maxn][maxn],z[maxn*maxn],cnt;

bool use[maxn*maxn];

void check(int p)
{
	memset(use,false,sizeof(use));
	if ((z[1]+z[2]+z[p])&1) return;
	res[1]=(z[1]+z[2]+z[p])/2-z[p];
	res[2]=z[1]-res[1];
	res[3]=z[2]-res[1];
	use[1]=use[2]=use[p]=true;
	for (int a=4,b=3;a<=n;a++)
	{
		while (b<=m && use[b])
			b++;
		if (b>m) return;
		res[a]=z[b]-res[1];
		use[b]=true;
		for (int c=2;c<a;c++)
		{
			if (res[c]>res[a]) return;
			int v=res[c]+res[a];
			int p=lower_bound(z+1,z+m+1,v)-z;
			if (z[p]!=v) return;
			int px=p;
			while (px && z[px]==z[p])
				px--;
			px++;
			while (px<=m && z[px]==z[p] && use[px])
				px++;
			if (z[px]!=z[p] || use[px]) return;
			p=px;
			use[p]=true;
		}
	}
	cnt++;
	for (int a=1;a<=n;a++)
		ans[cnt][a]=res[a];
}

int main()
{
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);

	scanf("%d",&n);
	m=n*(n-1)/2;
	for (int a=1;a<=m;a++)
		scanf("%d",&z[a]);
	sort(z+1,z+m+1);
	for (int a=3;a<=m;)
	{
		check(a);
		int b=a;
		while (b<=m && z[b]==z[a])
			b++;
		a=b;
	}
	printf("%d\n",cnt);
	for (int a=1;a<=cnt;a++)
		for (int b=1;b<=n;b++)
		{
			printf("%d",ans[a][b]);
			if (b==n) printf("\n");
			else printf(" ");
		}

	return 0;
}

