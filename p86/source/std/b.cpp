#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=1010;

int n,z[maxn],f[maxn];

int main()
{
	scanf("%d",&n);
	for (int a=1;a<=n;a++)
		scanf("%d",&z[a]);
	for (int a=1;a<=n;a++)
	{
		f[a]=max(f[a],1);
		for (int b=a+1;b<=n;b++)
			if (z[b]>z[a]) f[b]=max(f[b],f[a]+1);
	}
	int ans=0;
	for (int a=1;a<=n;a++)
		ans=max(ans,f[a]);
	printf("%d\n",ans);

	return 0;
}
