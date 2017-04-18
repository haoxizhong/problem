#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "face"
#define prename "c"

const int maxn=200010;

int x[maxn],y[maxn],z[maxn];

char djm[1000];

int cases=10;

int mode=1;

int getrand()
{
	return (rand()<<16)+rand();
}

void make_data(int test)
{
	int n=getrand()%50000+150000;
	int m=getrand()%10000+10000;
	printf("%d %d\n",n,m);
	for (int a=1;a<=n;a++)
		x[a]=a,y[a]=a,z[a]=a;
	random_shuffle(x+1,x+n+1);
	random_shuffle(y+1,y+n+1);
	random_shuffle(z+1,z+n+1);
	for (int a=1;a<=n;a++)
		printf("%d %d %d\n",x[a],y[a],z[a]);
	for (int a=1;a<=m;a++)
		printf("%d %d %d\n",getrand()%n+1,getrand()%n+1,getrand()%n+1);
}

int main()
{
	//srand(time(0));

	for (int a=1;a<=cases;a++)
	{
		fprintf(stderr,"%d\n",a);
		if (mode == 1)
		{
			sprintf(djm,problem "%d.in",a);
			freopen(djm,"w",stdout);

			make_data(a);

			fclose(stdout);

#ifdef unix
			sprintf(djm,"./" problem " < " problem "%d.in > " problem "%d.out",a,a);
#else
			sprintf(djm,problem ".exe < " problem "%d.in > " problem "%d.out",a,a);
#endif
			system(djm);
		}
		if (mode == 2)
		{
#ifdef unix
			sprintf(djm,"mv " prename "%d.in " problem "%d.in",a,a);
#else
			sprintf(djm,"rename " prename "%d.in " problem "%d.in",a,a);
#endif
			system(djm);

#ifdef unix
			sprintf(djm,"mv " prename "%d.out " problem "%d.out",a,a);
#else
			sprintf(djm,"rename " prename "%d.out " problem "%d.out",a,a);
#endif
			system(djm);
		}
	}

	return 0;
}
