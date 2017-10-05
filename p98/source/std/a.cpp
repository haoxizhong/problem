#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

long long n;

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf(LL,&n);
	long long ans=0,tmp=0;
	for (long long a=1,v;a*a<=(v=n/a);a++,ans++)
		for (long long b=a+1;b*b<=v;b++)
			tmp+=n/(a*b)-b;
	ans+=tmp*6;
	tmp=0;
	for (long long a=1,v;(v=a*a)<=n;a++)
	{
		tmp+=n/v;
		if (a*a<=n/a) tmp--;
	}
	ans+=tmp*3;
	printf(LL "\n",ans);

	return 0;
}
