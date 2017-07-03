#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define inc(a,b) {a+=b;if (a>=mo) a-=mo;}

const int mo=1000000007;

int f[70][2][2][2][2];

int get(long long n,int b,int k)
{
	for (;b--;)
		n/=k;
	return (int)(n%k);
}

int solve(long long n,long long m,int k)
{
	memset(f,0,sizeof(f));
	f[64][1][1][1][1]=1;
	for (int a=64;a;a--)
		for (int b=0;b<2;b++)
			for (int c=0;c<2;c++)
				for (int d=0;d<2;d++)
					for (int e=0;e<2;e++)
					if (f[a][b][c][d][e])
					{
						int nb=get(n,a-1,k);
						int mb=get(m,a-1,k);
						for (int ib=0;ib<k;ib++)
							for (int jb=0;jb<k;jb++)
							{
								if (b && ib>nb) continue;
								if (c && jb>mb) continue;
								if (d && jb>ib) continue;
								int newb,newc,newd,newe;
								if (b) newb=(ib==nb);
								else newb=0;
								if (c) newc=(jb==mb);
								else newc=0;
								if (d) newd=(ib==jb);
								else newd=0;
								if (e) newe=(jb<=ib);
								else newe=0;
								inc(f[a-1][newb][newc][newd][newe],f[a][b][c][d][e]);
							}
					}
	int ans=0;
	for (int a=0;a<=1;a++)
		for (int b=0;b<=1;b++)
			for (int c=0;c<=1;c++)
				inc(ans,f[0][a][b][c][0]);
	return ans;
}

int main()
{
	int t,k;
	scanf("%d%d",&t,&k);
	for (;t--;)
	{
		long long n,m;
		scanf("%lld%lld",&n,&m);
		printf("%d\n",solve(n,m,k));
	}

	return 0;
}
