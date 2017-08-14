#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=(1<<24)+10;

int n,z[30],q[2][maxn],y[maxn],way[30][1000][2];

char g[2][maxn]; 

int count(int a)
{
	int b=0;
	while (a)
		b+=a&1,a>>=1;
	return b;
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);

	scanf("%d",&n);
	if (n==1)
	{
		printf("1\n");
		return 0;
	}
	for (int a=1;a<=n;a++)
		scanf("%d",&z[a]);
	for (int a=2;a<=n;a++)
	{
		bool find=false;
		for (int b=0;b<a;b++)
			for (int c=b;c<a;c++)
				if (z[b]+z[c]==z[a]) 
				{
					find=true;
					way[a][0][0]++;
					way[a][way[a][0][0]][0]=b;
					way[a][way[a][0][0]][1]=c;
				}
		if (!find)
		{
			printf("-1\n");
			return 0;
		}
	}
	for (int a=0;a<(1<<(n+1));a++)
		y[a]=count(a);
	g[0][3]=1;
	g[0][2]=1;
	int size1=0,size2=0;
	size2=2;
	q[0][1]=2;q[0][2]=3;
	int now=1,nex=0;
	int nowans=100;
	for (int a=2;a<=n;a++)
	{
		now^=1;nex^=1;
		size1=size2;size2=0;
		for (int b=1;b<=size1;b++)
		{
			int s=q[now][b];
			if (nowans<y[s]) continue;
			nowans=min(nowans,y[s]+n-a+1);
			bool able=false;
			for (int f=1;f<=way[a][0][0];f++)
			{
				int c=way[a][f][0];
				int d=way[a][f][1];
				if ((s&(1<<c)) && (s&(1<<d)))
				{
					able=true;
					break;
				}
			}
			if (able)
			{
				for (int e=0;e<=n;e++)
					if (s&(1<<e))
					{
						int news=(s^(1<<e))|(1<<a);
						if (g[nex][news]!=a)
						{
							g[nex][news]=a;
							q[nex][++size2]=news;
						}
					}
				if (g[nex][s|(1<<a)]!=a)
				{
					g[nex][s|(1<<a)]=a;
					q[nex][++size2]=(s|(1<<a));
				}
			}
		}
	}
	int ans=nowans;
	for (int a=0;a<(1<<(n+1));a++)
		if (g[nex][a]==n) ans=min(ans,y[a]);
	printf("%d\n",ans);

	return 0;
}
