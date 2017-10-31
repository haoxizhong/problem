#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "tour"
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
	int n;
	if (test<=3) n=rand()%10+1;
	else if (test<=6) n=rand()%50+50;
	else n=getrand()%50000+50000;
	int k=rand()%min(max(n/3,2),1000)+1;
	printf("%d %d\n",n,k);
	for (int a=1;a<=n;a++)
		printf("%d%c",getrand()%n+1,a==n?'\n':' ');
	for (int a=2;a<=n;a++)
		printf("%d %d\n",getrand()%(a-1)+1,a);
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
