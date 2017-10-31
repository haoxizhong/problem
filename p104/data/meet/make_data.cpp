#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;

#define problem "meet"
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
	if (test<=3) n=rand()%5+1;
	else n=50;
	printf("%d\n",n);
	for (int a=1;a<=n;a++)
	{
		if (test>=6 && test<=7) printf("0");
		else printf("%d",getrand()%1000000+1);
		if (a==n) printf("\n");
		else printf(" ");
	}
	if (test>=4 && test<=5)
	{
		int h=getrand()%1000000+1;
		for (int a=1;a<=n;a++)
			printf("%d%c",h,a==n?'\n':' ');
	}
	else
	{
		for (int a=1;a<=n;a++)
			printf("%d%c",getrand()%1000000+1,a==n?'\n':' ');
	}
	if (test<=3) printf("%d\n",n*750000+getrand()%250000);
	else printf("%d\n",getrand()%5000000+5000000);
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
