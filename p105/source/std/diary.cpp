#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn=1000010;

int prime[maxn],cnt;

bool flag[maxn];

long long sum[maxn];

int main()
{
	freopen("diary.in","r",stdin);
	freopen("diary.out","w",stdout);

	for (int a=2;a<=1000000;a++)
	{
		if (!flag[a])
		{
			cnt++;
			prime[cnt]=a;
		}
		for (int b=1,c;b<=cnt && (c=a*prime[b])<=1000000;b++)
		{
			flag[c]=true;
			if (a % prime[b]==0) break;
		}
	}
	for (int a=1;a<=cnt;a++)
		sum[a]=prime[a]+sum[a-1];
	int t;
	scanf("%d",&t);
	for (;t--;)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		int l=1,r=cnt-k+2;
		if (r<=1)
		{
			printf("-1\n");
			continue;
		}
		while (l+1!=r)
		{
			int m=(l+r)>>1;
			if (sum[m+k-1]-sum[m-1]>n) r=m;
			else l=m;
		}
		if (sum[l+k-1]-sum[l-1]<=n) printf("%d\n",(int)(sum[l+k-1]-sum[l-1]));
		else printf("-1\n");
	}

	return 0;
}
