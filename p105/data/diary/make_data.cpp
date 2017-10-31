#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "diary"
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
	int t=rand()%1000+1000;
	int nx=getrand()%500000+500000;
	if (test<=2) t=rand()%100+100;
	if (test>=3 && test<=4) t=1;
	printf("%d\n",t);
	for (;t--;)
	{
		int n;
		if (test<=2) n=rand()%100+1;
		else if (test>=5 && test<=6) n=nx;
		else n=getrand()%1000000+1;
		printf("%d %d\n",n,rand()%100+1);
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
