#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=5000010;
const int mo=1000000007;

int n,cnt,f[maxn],er[maxn],divisor[maxn];

#define inc(a,b) a+=b,(a>=mo ? a-=mo : 0)

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	scanf("%d",&n);
	for (int a=2;a<=n;a++)
		f[a]=f[a-2],inc(f[a],a/3-a/4);
	for (int a=1;a*a<=n;a++)
		if (n % a==0)
		{
			cnt++;
			divisor[cnt]=a;
			if (a*a!=n)
			{
				cnt++;
				divisor[cnt]=n/a;
			}
		}
	sort(divisor+1,divisor+cnt+1);
	for (int a=1;a<=cnt;a++)
		for (int b=1;b<a;b++)
			if (divisor[a] % divisor[b]==0) inc(f[divisor[a]],mo-f[divisor[b]]);
	er[0]=1;
	for (int a=1;a<=n;a++)
		er[a]=er[a-1],inc(er[a],er[a-1]);
	int ans=0;
	for (int a=1;a<=cnt;a++)
		inc(ans,(long long)f[divisor[a]]*er[n/divisor[a]-1]%mo);
	printf("%d\n",ans);

	return 0;
}
