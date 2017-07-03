#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=110;

bool use[400];

struct data
{
	int n,q;
	int e[maxn],s[maxn];
	int dis[maxn][maxn];
	int z[maxn][2];

	void init()
	{
		scanf("%d%d",&n,&q);
		for (int a=1;a<=n;a++)
			scanf("%d%d",&e[a],&s[a]);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				scanf("%d",&dis[a][b]);
		for (int a=1;a<=q;a++)
			scanf("%d%d",&z[a][0],&z[a][1]);
	}

	void output()
	{
		printf("%d %d\n",n,q);
		for (int a=1;a<=n;a++)
			printf("%d %d\n",e[a],s[a]);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=n;b++)
				printf("%d%c",dis[a][b],b==n?'\n':' ');
		for (int a=1;a<=q;a++)
			printf("%d %d\n",z[a][0],z[a][1]);
	}

	bool operator<(const data &a)const
	{
		return n+q<a.n+q;
	}
}D[310];

void generate(int &cnt,int id)
{
	char djm[100];

	cnt++;

	sprintf(djm,"%d.in",cnt);

	freopen(djm,"w",stdout);

	D[id].output();

	fclose(stdout);

	sprintf(djm,"std.exe < %d.in > %d.out",cnt,cnt);

	system(djm);
}

int main()
{
	freopen("in","r",stdin);
	int T;
	scanf("%d",&T);
	for (int a=1;a<=T;a++)
		D[a].init();
	sort(D+1,D+T+1);
	int cnt=0;
	for (int a=273;a<=300;a+=3)
	{
		use[a]=true;
		generate(cnt,a);
	}
	while (cnt<25)
	{
		int p=300;
		while (use[p])
			p=rand()%300+1;
		use[p]=true;
		generate(cnt,p);
	}

	return 0;
}
