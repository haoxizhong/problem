#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=10010;

int n,m,n1,n2,y[maxn],z[maxn],sum[maxn];

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	int t;
	scanf("%d",&t);
	for (;t--;)
	{
		scanf("%d%d%d%d",&n,&m,&n1,&n2);
		for (int a=1;a<=n1;a++)
			scanf("%d",&y[a]);
		for (int a=1;a<=n2;a++)
			scanf("%d",&z[a]);
		sort(y+1,y+n1+1,cmp);
		sort(z+1,z+n2+1,cmp);
		for (int a=1;a<=n1;a++)
			y[a]+=y[a-1];
		for (int a=1;a<=n2;a++)
			z[a]+=z[a-1];
		int delta;
		if (n%3==2 && m%3==2 && (n==2 || m==2)) delta=4;
		else delta=n*m%3;
		int ans=0,limit=min(n2,(n*m-delta)/3);
		for (int a=0;a<=limit;a++)
			ans=max(ans,z[a]+y[min(n1,(n*m-a*3)>>1)]);
		printf("%d\n",ans);
	}

	return 0;
}
