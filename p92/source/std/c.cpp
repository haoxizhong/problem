#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn=10000000;

int n,top[10],place[10],res[maxn],q[maxn],bit[10],front,tail,w[10],z[10];

bool use[maxn];

bool cmp(int a,int b)
{
	return w[a]<w[b];
}

void analyze(int s)
{
	int x=0;
	int ss=s;
	for (int a=1;a<=7;a++)
		top[a]=0;
	while (ss)
	{
		x++;
		place[x]=ss%10;
		ss/=10;
	}
	reverse(place+1,place+x+1);
	for (int a=x;a>=1;a--)
		top[place[a]]=a;
	for (int a=1;a<=x;a++)
		if (a==top[place[a]])
		{
			int p=place[a];
			if (p!=1 && (a<top[p-1] || !top[p-1]))
			{
				int news=s-bit[x-a];
				if (!use[news])
				{
					q[++tail]=news;
					use[news]=true;
					res[news]=res[s]+1;
				}
			}
			if (p!=x && (a<top[p+1] || !top[p+1]))
			{
				int news=s+bit[x-a];
				if (!use[news])
				{
					q[++tail]=news;
					use[news]=true;
					res[news]=res[s]+1;
				}
			}
		}
}

int main()
{
	front=1,tail=0;
	int status=0;
	bit[0]=1;
	for (int a=1;a<=7;a++)
	{
		bit[a]=bit[a-1]*10;
		status=status*10+a;
		q[++tail]=status;
		use[status]=true;
	}
	for (;front<=tail;)
	{
		int s=q[front++];
		analyze(s);
	}
	int t;
	scanf("%d",&t);
	for (;t--;)
	{
		scanf("%d",&n);
		for (int a=1;a<=n;a++)
			scanf("%d",&w[a]),z[a]=a;
		sort(z+1,z+n+1,cmp);
		int s=0;
		for (int a=1;a<=n;a++)
			s=s*10+z[a];
		if (!use[s]) printf("-1\n");
		else printf("%d\n",res[s]);
	}

	return 0;
}
