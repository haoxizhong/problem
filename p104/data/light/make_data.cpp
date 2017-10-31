#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "light"
#define prename "a"

char djm[1000];

int cases=10;

int mode=1;

int getrand()
{
	return (rand()<<15)+rand();
}

void make_data(int test)
{
	int n,m;
	if (test<=3) n=rand()%1000+1,m=rand()%1000+1;
	else n=getrand()%50000+50000,m=getrand()%50000+50000;
	int px=getrand()%5000+5000;
	printf("%d %d\n",n,m);
	for (int a=1;a<=n;a++)
		printf("%d%c",rand()%10000+1,a==n?'\n':' ');
	for (int a=1;a<=m;a++)
	{
		int l,r,p,v;
		l=getrand()%n+1,r=getrand()%n+1;
		if (l>r) swap(l,r);
		if (test>=4 && test<=6) p=px;
		else if (rand()%2) p=getrand()%100+1;
		else p=getrand()%9900+101;
		v=getrand()%p;
		printf("%d %d %d %d\n",l,r,p,v);
	}
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
