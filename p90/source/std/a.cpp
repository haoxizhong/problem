#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

int q[100][2];

bool use[11][11];

char s[11][11],map[11][11];

bool equal(char a,char b)
{
	return	a==b || (a=='M' && (b=='R' || b=='B' || b=='Y')) || (b=='M' && (a=='R' || a=='B' || a=='Y'));
}

bool del()
{
	bool res=false;
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			if (map[a][b]!='\0')
			{
				if (a<=6 && equal(map[a][b],map[a+1][b]) && equal(map[a][b],map[a+2][b]) && equal(map[a+1][b],map[a+2][b])) use[a][b]=use[a+1][b]=use[a+2][b]=res=true;
				if (b<=6 && equal(map[a][b],map[a][b+1]) && equal(map[a][b],map[a][b+2]) && equal(map[a][b+1],map[a][b+2])) use[a][b]=use[a][b+1]=use[a][b+2]=res=true;
			}
	int front=1,tail=0;
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			if (map[a][b]=='#' && use[a][b]) q[++tail][0]=a,q[tail][1]=b;
	for (;front<=tail;)
	{
		int x=q[front][0];
		int y=q[front++][1];
		for (int a=-1;a<=1;a++)
			for (int b=-1;b<=1;b++)
				if (a!=0 || b!=0)
				{
					if (!use[x+a][y+b])
					{
						use[x+a][y+b]=true;
						if (map[x+a][y+b]=='#')
						{
							q[++tail][0]=x+a;
							q[tail][1]=y+b;
						}
					}
				}
	}
	return res;
}

int calc()
{
	int ans=0;
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			if (use[a][b] && map[a][b]!='\0') ans++;
	return ans;
}

void down()
{
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			if (use[a][b]) map[a][b]='\0';
	memset(use,false,sizeof(use));
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			if (map[a][b]!='\0')
			{
				int c=a;
				while (c>1 && map[c-1][b]=='\0')
					c--;
				if (c!=a)
				{
					map[c][b]=map[a][b];
					map[a][b]='\0';
				}
			}
}

int solve()
{
	memset(map,0,sizeof(map));
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
			map[a][b]=s[a][b];
	int ans=0;
	while (del())
	{
		ans+=calc();
		down();
	}
	return ans;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	for (int a=8;a>=1;a--)
		scanf("%s",s[a]+1);
	int ans=0,sol=0;
	for (int a=1;a<=8;a++)
		for (int b=1;b<=8;b++)
		{
			if (a<8)
			{
				swap(s[a][b],s[a+1][b]);
				int v=solve();
				if (v>ans)
				{
					ans=v;
					sol=1;
				}
				else 
				{
					if (v==ans) sol++;
				}
				swap(s[a][b],s[a+1][b]);
			}
			if (b<8)
			{
				swap(s[a][b],s[a][b+1]);
				int v=solve();
				if (v>ans)
				{
					ans=v;
					sol=1;
				}
				else
				{
					if (v==ans) sol++;
				}
				swap(s[a][b],s[a][b+1]);
			}
		}
	printf("%d %d\n",ans,sol);

	return 0;
}
