#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<set>

using namespace std;

const int maxn=50;

int n,m,f[maxn][maxn][maxn][maxn][2],pos[maxn][maxn][2];

char s[maxn][maxn],map[maxn][maxn];

int dfs(int x1,int y1,int x2,int y2,int odd)
{
	if (x1>x2 || y1>y2) return 0;
	if (f[x1][y1][x2][y2][odd]!=-1) return f[x1][y1][x2][y2][odd];
	int &t=f[x1][y1][x2][y2][odd];
	t=0;
	set<int> se;
	for (int a=x1;a<=x2;a++)
		for (int b=y1;b<=y2;b++)
			if ((b&1)==odd)
			{
				if (map[a][b]=='L') se.insert(dfs(x1,y1,a-1,y2,odd)^dfs(a+1,y1,x2,y2,odd));
				else
				{
					if (map[a][b]=='R') se.insert(dfs(x1,y1,x2,b-1,odd)^dfs(x1,b+1,x2,y2,odd));
					else
					{
						if (map[a][b]=='X') se.insert(dfs(x1,y1,a-1,b-1,odd)^dfs(x1,b+1,a-1,y2,odd)^dfs(a+1,y1,x2,b-1,odd)^dfs(a+1,b+1,x2,y2,odd));
					}
				}
			}
	while (se.count(t))
		t++;
	return t;
}

int main()
{
	freopen("wjwd.in","r",stdin);
	freopen("wjwd.out","w",stdout);

	while (~scanf("%d%d",&n,&m))
	{
		for (int a=1;a<=n;a++)
			scanf("%s",s[a]+1);
		memset(pos,0,sizeof(pos));
		memset(map,0,sizeof(map));
		pos[1][1][0]=1;pos[1][1][1]=n;
		for (int a=2;a<=m;a++)
			pos[1][a][0]=pos[1][a-1][0]+1,pos[1][a][1]=pos[1][a-1][1]+1;
		for (int a=2;a<=n;a++)
			pos[a][1][0]=pos[a-1][1][0]+1,pos[a][1][1]=pos[a-1][1][1]-1;
		for (int a=2;a<=n;a++)
			for (int b=2;b<=m;b++)
				pos[a][b][0]=pos[a-1][b][0]+1,pos[a][b][1]=pos[a][b-1][1]+1;
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
				map[pos[a][b][0]][pos[a][b][1]]=s[a][b];
		memset(f,-1,sizeof(f));
		if (dfs(1,1,n+m-1,n+m-1,0)^dfs(1,1,n+m-1,n+m-1,1)) printf("WIN\n");
		else printf("LOSE\n");
	}

	return 0;
}
