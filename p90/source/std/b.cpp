#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=1010;
const int INF=0x3f3f3f3f;

int n,m,z[maxn][maxn],y[maxn][maxn],down[maxn][maxn],right[maxn][maxn];

void readint(int &x)
{
	x=0;
	char c=' ';
	while (!(c>='0' && c<='9'))
		c=(char)getchar();
	while (c>='0' && c<='9')
	{
		x=x*10+c-'0';
		c=(char)getchar();
	}
}

bool check(int v)
{
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			y[a][b]=(z[a][b]>=v);
	for (int a=n;a>=1;a--)
		for (int b=m;b>=1;b--)
		{
			if (y[a][b+1]) right[a][b]=b+1;
			else right[a][b]=right[a][b+1];
			if (y[a+1][b]) down[a][b]=a+1;
			else down[a][b]=down[a+1][b];
		}
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
			if (y[a][b])
			{
				for (int c=down[a][b];c;c=down[c][b])
					for (int d=right[a][b];d;d=right[a][d])
						if (y[c][d]) return true;
			}
	return false;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);

	readint(n);
	readint(m);
	int l=INF,r=-INF;
	for (int a=1;a<=n;a++)
		for (int b=1;b<=m;b++)
		{
			readint(z[a][b]);
			l=min(l,z[a][b]);
			r=max(r,z[a][b]);
		}
	r++;
	while (l+1!=r)
	{
		int m=(l+r)>>1;
		if (check(m)) l=m;
		else r=m;
	}
	printf("%d\n",l);

	return 0;
}
