#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define inc(a,b) {a+=b;if (a>=mo) a-=mo;}

const int mo=10007;

int n,m,f[2][7][1<<6][1<<6][2][2],z[70][10];

void solve(int o,int u)
{
	memset(f[o],0,sizeof(f[o]));
	for (int st=0;st<(1<<m);st++)
		for (int ts=0;ts<(1<<m);ts++)
			f[o][0][st][ts][0][0]=f[o^1][m][st][ts][0][0];
	for (int k=0;k<m;k++)
		for (int st=0;st<(1<<m);st++)
			for (int ts=0;ts<(1<<m);ts++)
				for (int a=0;a<2;a++)
					for (int b=0;b<2;b++)
						if (f[o][k][st][ts][a][b])
						{
							int resa=(st>>k)&1;
							int resb=(ts>>k)&1;
							resa+=a;resb+=b;
							if (z[u][k+1]!=-1 && (resa>z[u][k+1] || resb>z[u][k+1])) continue;
							for (int x1=0;x1<2;x1++)
								for (int x2=0;x2<2;x2++)
									for (int y1=0;y1<2;y1++)
										for (int y2=0;y2<2;y2++)
										{
											int nexa=x1+x2+resa;
											int nexb=y1+y2+resb;
											if (nexa!=nexb) continue;
											if (z[u][k+1]!=-1 && (nexa!=z[u][k+1] || nexb!=z[u][k+1])) continue;
											int st_=st^(st&(1<<k));
											int ts_=ts^(ts&(1<<k));
											st_^=(x1<<k);
											ts_^=(y1<<k);
											inc(f[o][k+1][st_][ts_][x2][y2],f[o][k][st][ts][a][b]);
										}
						}
}

int main()
{
	int t;
	scanf("%d",&t);
	for (;t--;)
	{
		scanf("%d%d",&n,&m);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
				scanf("%d",&z[a][b]);
		memset(f,0,sizeof(f));
		f[0][m][0][0][0][0]=1;
		int now=1;
		for (int a=1;a<=n;a++)
		{
			solve(now,a);
			now^=1;
		}
		printf("%d\n",f[now^1][m][0][0][0][0]);
	}

	return 0;
}
