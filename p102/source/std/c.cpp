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

const int maxn=100010;
const int mo=1000000007;

int n,m,r,c,ans,v0[maxn],v1[maxn],v2[maxn],v3[maxn],v4[maxn];

long long s;

int multi(long long a,int b)
{
	a*=b;
	if (a>=mo) a%=mo;
	return (int)a;
}

void inc(int &a,int b)
{
	a+=b;
	if (a>=mo) a-=mo;
}

int mul(int a,int b)
{
	int ans=1;
	while (b)
	{
		if (b&1) ans=multi(ans,a);
		a=multi(a,a);
		b>>=1;
	}
	return ans;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	scanf("%d%d%d%d" LL,&n,&m,&r,&c,&s);
	v1[0]=1;
	for (int a=1;a<=100000;a++)
		v0[a]=mul(a,mo-2);
	int tmp=1;
	for (int a=0;a<=(r>>1);a++)
	{
		v1[a]=tmp;
		tmp=multi(tmp,multi(a+n,v0[a+1]));
	}
	tmp=1;
	for (int a=0;a<=(c>>1);a++)
	{
		v2[a]=tmp;
		tmp=multi(tmp,multi(a+m,v0[a+1]));
	}
	tmp=1;
	for (int a=0;a<=n;a++)
	{
		v3[a]=tmp;
		tmp=multi(tmp,multi(n-a,v0[a+1]));
	}
	tmp=1;
	for (int a=0;a<=m;a++)
	{
		v4[a]=tmp;
		tmp=multi(tmp,multi(m-a,v0[a+1]));
	}
	for (int a=r&1;a<=min(n,r);a+=2)
		if (a*2!=n)
		{
			if (((s-(long long)a*m))%(n-a*2)) continue;
			int b=(int)((s-(long long)a*m)/(n-a*2));
			if (b>c || b<0 || ((c-b)&1)) continue;
			int nowans=v3[a];
			nowans=multi(nowans,v1[(r-a)>>1]);
			nowans=multi(nowans,v4[b]);
			nowans=multi(nowans,v2[(c-b)>>1]);
			inc(ans,nowans);
		}
		else
		{
			if ((long long)a*m!=s) continue;
			int nowans=v3[a];
			nowans=multi(nowans,v1[(r-a)>>1]);
			int cnt=0;
			for (int b=(c&1);b<=min(r,c);b+=2)
				inc(cnt,multi(v4[b],v2[(c-b)>>1]));
			inc(ans,multi(ans,cnt));
		}
	printf("%d\n",ans);

	return 0;
}
