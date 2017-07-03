#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=100010;

int s,k,f[maxn];

int main()
{
	int test;
	scanf("%d",&test);
	for (;test--;)
	{
		scanf("%d%d",&s,&k);
		memset(f,0x3f,sizeof(f));
		for (int a=1;a<=s;a++)
			for (int b=1;b<=a;b++)
				if (f[a-b]>k*b) f[a]=min(f[a],b);
		if (f[s]<s) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}
