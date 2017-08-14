#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define inc(a,b) {a+=b;if (a>=mo) a-=mo;}

const int maxn=1000010;
const int mo=1000000009;

int n,m,f[maxn];

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	scanf("%d%d",&m,&n);
	if (n==0)
	{
		printf("1\n");
		return 0;
	}
	if (m<=1)
	{
		printf("0\n");
		return 0;
	}
	f[0]=1;
	f[1]=1;
	for (int a=2;a<m;a++)
		f[a]=(int)((long long)f[a-1]*2%mo);
	int nowsum=0;
	for (int a=0;a<m;a++)
		inc(nowsum,f[a]);
	nowsum--;
	if (nowsum<0) nowsum+=mo;
	f[0]=0;
	for (int a=m;a<=n;a++)
	{
		f[a]=nowsum;
		nowsum-=f[a-m];
		if (nowsum<0) nowsum+=mo;
		inc(nowsum,f[a]);
	}
	f[0]=1;
	printf("%d\n",f[n]);

	return 0;
}
