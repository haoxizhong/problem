#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int mo=1000000000;

int n,limit[10],up,down[10];

char s[100];

int f[2][6][6][4][1010][3];

struct rec
{
	int opt,v,c;
	bool operator<(const rec &a)const
	{
		return v<a.v;
	}
}z[510];

void update(int a,int b,int c,int d,int e,int newv,int newn,int last)
{
	if (f[a][b][c][d][e][0]<newv)
	{
		f[a][b][c][d][e][0]=newv;
		f[a][b][c][d][e][1]=0;
		f[a][b][c][d][e][2]=last;

	}
	if (f[a][b][c][d][e][0]==newv && f[a][b][c][d][e][2]<last)
	{
		f[a][b][c][d][e][1]=0;
		f[a][b][c][d][e][2]=last;
	}
	if (f[a][b][c][d][e][0]==newv && f[a][b][c][d][e][2]==last)
	{
		f[a][b][c][d][e][1]+=newn;
		if (f[a][b][c][d][e][1]>mo) f[a][b][c][d][e][1]=mo;
	}
}

void update(int p)
{
	for (int a=limit[0]-(z[p].opt==0);a>=0;a--)
		for (int b=limit[1]-(z[p].opt==1);b>=0;b--)
			for (int c=limit[2]-(z[p].opt==2);c>=0;c--)
				for (int d=limit[3]-(z[p].opt==3);d>=0;d--)
					if (a+b+c+d<11)
					{
						for (int e=up-z[p].c;e>=0;e--)
							if (f[a][b][c][d][e][1])
							{
								int newv=f[a][b][c][d][e][0]+z[p].v;
								update(a+(z[p].opt==0),b+(z[p].opt==1),c+(z[p].opt==2),d+(z[p].opt==3),e+z[p].c,newv,f[a][b][c][d][e][1],z[p].v);
							}
					}
}

int main()
{
	freopen("wosa.in","r",stdin);
	freopen("wosa.out","w",stdout);

	int test;
	test=1;
	for (;test--;)
	{
		scanf("%d",&n);
		down[0]=1;down[1]=3;down[2]=2;down[3]=1;
		limit[0]=1;limit[1]=5;limit[2]=5;limit[3]=3;
		memset(f,0,sizeof(f));
		f[0][0][0][0][0][1]=1;
		f[0][0][0][0][0][2]=-1;
		for (int a=1;a<=n;a++)
		{
			scanf("%s",s);
			int v,c;
			scanf("%d%d",&v,&c);
			if (s[0]=='G') z[a].opt=0;
			if (s[0]=='D') z[a].opt=1;
			if (s[0]=='M') z[a].opt=2;
			if (s[0]=='F') z[a].opt=3;
			z[a].v=v;z[a].c=c;
		}
		scanf("%d",&up);
		sort(z+1,z+n+1);
		for (int a=1;a<=n;a++)
			update(a);
		int resv=0,resc=0x3f3f3f3f,resn=0;
		for (int a=down[0];a<=limit[0];a++)
			for (int b=down[1];b<=limit[1];b++)
				for (int c=down[2];c<=limit[2];c++)
					for (int d=down[3];d<=limit[3];d++)
						if (a+b+c+d==11)
							for (int e=0;e<=up;e++)
								if (f[a][b][c][d][e][1])
								{
									int nowv=f[a][b][c][d][e][0]+f[a][b][c][d][e][2];
									int nowc=e;
									int nown=f[a][b][c][d][e][1];
									if (nowv>resv)
									{
										resv=nowv;
										resc=nowc;
										resn=0;
									}
									if (nowv==resv && nowc<resc)
									{
										resc=nowc;
										resn=0;
									}
									if (nowv==resv && nowc==resc)
									{
										resn+=nown;
										if (resn>mo) resn=mo;
									}
								}
		printf("%d %d %d\n",resv,resc,resn);
	}

	return 0;
}
