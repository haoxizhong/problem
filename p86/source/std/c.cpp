#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=600;

char s1[maxn],s2[maxn];

int f[maxn][maxn];

int main()
{
	scanf("%s%s",s1+1,s2+1);
	int l1=strlen(s1+1);
	int l2=strlen(s2+1);
	for (int a=1;a<=l1;a++)
		for (int b=1;b<=l2;b++)
		{
			f[a][b]=max(f[a-1][b],f[a][b-1]);
			if (s1[a]==s2[b]) f[a][b]=max(f[a][b],f[a-1][b-1]+1);
		}
	printf("%d\n",f[l1][l2]);

	return 0;
}
