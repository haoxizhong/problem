#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define now pre[a][b][c][d][e][s1][s2][s3][s4]
#define dis(a,b,c,d) (abs(a-c)+abs(b-d))

const int INF=0x3f3f3f3f;

int A,B,C,D,E,num[10][10],value[10][10][10],delta[10][10][40],dp[31][6][6][6][6][2][2][2][2];

char s[500];

bool map[6][6][6][6];

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	scanf("%d%d%d%d%d",&A,&B,&C,&D,&E);
	for (int a=0;a<6;a++)
	{
		scanf("%s",s);
		int p=0;
		for (int b=0;b<6;b++)
		{
			int px=p;
			while (s[px]!=']')
				px++;
			p++;
			num[a][b]=s[p]-'0';
			p++;
			p++;
			for (int c=1;c<=num[a][b];c++)
			{
				int v=0;
				while (s[p]>='0' && s[p]<='9')
				{
					v=v*10+s[p]-'0';
					p++;
				}
				value[a][b][c]=v;
				p++;
			}
			p=px+1;
		}
	}
	int base=0;
	for (int a=0;a<6;a++)
		for (int b=0;b<6;b++)
			if (a>=2 && a<=3 && b>=2 && b<=3) ;
			else
			{
				sort(value[a][b]+1,value[a][b]+num[a][b]+1);
				for (int c=2;c<=num[a][b];c++)
					if (value[a][b][c]-value[a][b][c-1]==1) base+=A;
				for (int c=2;c<=3;c++)
					for (int d=2;d<=3;d++)
					{
						if (dis(a,b,c,d)==1)
						{
							for (int e=1;e<=num[a][b];e++)
							{
								delta[c][d][value[a][b][e]]+=B;
								delta[c][d][value[a][b][e]-1]+=C;
								delta[c][d][value[a][b][e]+1]+=C;
							}
						}
						if (dis(a,b,c,d)==2)
						{
							for (int e=1;e<=num[a][b];e++)
							{
								delta[c][d][value[a][b][e]]+=D;
								delta[c][d][value[a][b][e]-1]+=E;
								delta[c][d][value[a][b][e]+1]+=E;
							}
						}
					}
				for (int c=0;c<6;c++)
					for (int d=0;d<6;d++)
						if (dis(a,b,c,d)<=2 && (c!=a || d!=b) && !map[a][b][c][d])
						{
							map[a][b][c][d]=map[c][d][a][b]=true;
							if (c>=2 && c<=3 && d>=2 && d<=3) ;
							else
							{
								int dist=dis(a,b,c,d);
								for (int e=1;e<=num[a][b];e++)
									for (int f=1;f<=num[c][d];f++)
									{
										if (abs(value[a][b][e]-value[c][d][f])==0)
										{
											if (dist==1) base+=B;
											else base+=D;
										}
										if (abs(value[a][b][e]-value[c][d][f])==1)
										{
											if (dist==1) base+=C;
											else base+=E;
										}
									}
							}
						}
			}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0][0][0][0][0][0][0][0]=base;
	for (int a=0;a<30;a++)
		for (int b=0;b<=num[2][2];b++)
			for (int c=0;c<=num[2][3];c++)
				for (int d=0;d<=num[3][2];d++)
					for (int e=0;e<=num[3][3];e++)
						for (int s1=0;s1<=1;s1++)
							for (int s2=0;s2<=1;s2++)
								for (int s3=0;s3<=1;s3++)
									for (int s4=0;s4<=1;s4++)
										if (dp[a][b][c][d][e][s1][s2][s3][s4]!=INF)
										{
											int v=dp[a][b][c][d][e][s1][s2][s3][s4];
											for (int sx1=0;sx1<=(b!=num[2][2]);sx1++)
												for (int sx2=0;sx2<=(c!=num[2][3]);sx2++)
													for (int sx3=0;sx3<=(d!=num[3][2]);sx3++)
														for (int sx4=0;sx4<=(e!=num[3][3]);sx4++)
														{
															int wmt=0;
															if (sx1) 
															{
																wmt+=delta[2][2][a+1];
																if (s1) wmt+=A;
																if (s2) wmt+=C;
																if (s3) wmt+=C;
																if (s4) wmt+=E;
															}
															if (sx2) 
															{
																wmt+=delta[2][3][a+1];
																if (s1) wmt+=C;
																if (s2) wmt+=A;
																if (s3) wmt+=E;
																if (s4) wmt+=C;
															}
															if (sx3) 
															{
																wmt+=delta[3][2][a+1];
																if (s1) wmt+=C;
																if (s2) wmt+=E;
																if (s3) wmt+=A;
																if (s4) wmt+=C;
															}
															if (sx4) 
															{
																wmt+=delta[3][3][a+1];
																if (s1) wmt+=E;
																if (s2) wmt+=C;
																if (s3) wmt+=C;
																if (s4) wmt+=A;
															}
															if (sx1 && sx2) wmt+=B;
															if (sx1 && sx3) wmt+=B;
															if (sx1 && sx4) wmt+=D;
															if (sx2 && sx3) wmt+=D;
															if (sx2 && sx4) wmt+=B;
															if (sx3 && sx4) wmt+=B;
															int &t=dp[a+1][b+sx1][c+sx2][d+sx3][e+sx4][sx1][sx2][sx3][sx4];
															if (t>v+wmt) t=v+wmt;
														}
										}
	int ans=INF;
	for (int a=0;a<=1;a++)
		for (int b=0;b<=1;b++)
			for (int c=0;c<=1;c++)
				for (int d=0;d<=1;d++)
					ans=min(ans,dp[30][num[2][2]][num[2][3]][num[3][2]][num[3][3]][a][b][c][d]);
	printf("%d\n",ans);

	return 0;
}
