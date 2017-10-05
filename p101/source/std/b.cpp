#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

const int maxn=110;
const int maxs=maxn*maxn/2;
const int mo=905229641;

long long n;

int m,f[maxn][maxs],fac[maxn];

int calc(long long a,long long b)
{
	long long ans=1;
	for (int c=1;c<a;c++)
		ans=ans*(b+c)%mo;
	return (int)ans;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);

	scanf(LL "%d",&n,&m);
	f[0][0]=1;
	int up=m*(m-1)/2;
	for (int a=0;a<m;a++)
		for (int b=m;b>=0;b--)
			for (int c=up;c>=0;c--)
				if (f[b][c]) f[b+1][c+a]=(f[b+1][c+a]+f[b][c])%mo;
	fac[0]=1;
	for (int a=1;a<=m;a++)
		fac[a]=(long long)fac[a-1]*a%mo;
	int x=(int)(n%m);
	int ans=0;
	for (int a=x;a<=n && a<=up;a+=m)
	{
		long long rest=(n-a)/m;
		for (int b=1;b<=m;b++)
			if (f[b][a])
			{
				int nowans=calc(b,rest%mo);
				nowans=(long long)nowans*f[b][a]%mo;
				nowans=(long long)nowans*b%mo;
				ans=(ans+nowans)%mo;
			}
	}
	printf("%d\n",ans);

	return 0;
}
