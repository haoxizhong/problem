#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>

using namespace std;

const int maxn=1000010;

int n,ans,p[26][26],minv[26][26],sum[26],last[26];

char s[maxn];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d",&n);
	scanf("%s",s+1);
	for (int a=1;a<=n;a++)
	{
		int c=s[a]-'a';
		sum[c]++;
		last[c]=a;
		for (int b=0;b<26;b++)
			if (b!=a && sum[b]) ans=max(ans,max(sum[c]-sum[b]-minv[c][b]-(last[b]==p[c][b]),sum[b]-sum[c]-minv[b][c]-(last[b]==p[b][c])));
		for (int b=0;b<26;b++)
		{
			if (sum[c]-sum[b]<minv[c][b]) minv[c][b]=sum[c]-sum[b],p[c][b]=a;
			if (sum[b]-sum[c]<minv[b][c]) minv[b][c]=sum[b]-sum[c],p[b][c]=a;
		}
	}
	printf("%d\n",ans);

	return 0;
}
