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

#define lb(x) ((x)&(-(x)))

const int maxn=100010;

int n,z[maxn],y[maxn],x[maxn];

long long k;

bool cmp(int a,int b)
{
	return z[a]<z[b];
}

void insert(int *z,int p,int d)
{
	for (;p<=n;p+=lb(p))
		z[p]+=d;
}

int query(int *z,int p)
{
	int ans=0;
	for (;p;p-=lb(p))
		ans+=z[p];
	return ans;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d" LL,&n,&k);
	for (int a=1;a<=n;a++)
		scanf("%d",&z[a]),y[a]=a;
	sort(y+1,y+n+1,cmp);
	x[y[1]]=1;
	for (int a=2;a<=n;a++)
		if (z[y[a]]==z[y[a-1]]) x[y[a]]=x[y[a-1]];
		else x[y[a]]=x[y[a-1]]+1;
	for (int a=1;a<=n;a++)
		z[a]=x[a];
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	long long nowans=0;
	int p=n;
	while (p>=1)
	{
		nowans+=query(y,z[p]-1);
		insert(y,z[p],1);
		p--;
	}
	p++;
	long long ans=0;
	for (int a=1;a<=n;a++)
	{
		if (p==a)
		{
			nowans-=a-1-query(x,z[p])+query(y,z[p]-1);
			insert(y,z[p],-1);
			p++;
		}
		nowans+=a-1-query(x,z[a])+query(y,z[a]-1);
		insert(x,z[a],1);
		while (nowans>k && p<=n)
		{
			nowans-=a-query(x,z[p])+query(y,z[p]-1);
			insert(y,z[p],-1);
			p++;
		}
		if (nowans<=k) ans+=n-p+1;
	}
	printf(LL "\n",ans);

	return 0;
}
