#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "noname"
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
	printf("%d %d\n",n,m);
	for (int a=1;a<=n;a++)
		printf("%d%c",getrand()%n+1,a==n?'\n':' ');
	for (int a=1;a<=m;a++)
	{
		int opt=rand()%2;
		if (test>=6 && test<=7) opt=0;
		int l=getrand()%n+1,r=getrand()%n+1;
		if (l>r) swap(l,r);
		int k=rand()%10+1;
		if (test>=4 && test<=5) k=1;
		int v=getrand()%n+1;
		if (!opt) printf("%d %d %d %d\n",opt,l,r,k);
		else printf("%d %d %d %d\n",opt,l,r,v);
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
