#include<cstdio>
#include<cstdlib>
#include<cstring>
 
using namespace std;

long long n,f[2][2];

int k,bit[60];

int main()
{
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);

	while (~scanf("%I64d%d",&n,&k))
	{
		int num=0;
		while (n)
			bit[++num]=n%k,n/=k;
		if (num&1) f[1][0]=bit[num],f[1][1]=1;
		else f[1][0]=1,f[1][1]=0;
		int now=1,last=0;
		for (int a=num-1;a>=1;a--)
		{
			now^=1;last^=1;
			if (a&1) f[now][0]=f[last][0]*k+f[last][1]*bit[a],f[now][1]=f[last][1]; 
			else
			{
				f[now][0]=f[last][0];
				f[now][1]=0;
				if (!bit[a]) f[now][1]=f[last][1];
				else f[now][0]+=f[last][1];
			}
		}
		printf("%I64d\n",f[now][0]+f[now][1]);
	}

	return 0;
}
