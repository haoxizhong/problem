#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int n,m;

int main()
{
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);

	while (~scanf("%d%d",&n,&m))
	{
		if (!n && !m) break;
		if ((n&1)&&(m&1)) printf("Chito\n");
		else printf("Yuri\n");
	}

	return 0;
}
