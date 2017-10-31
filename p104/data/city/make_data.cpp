#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "city"
#define prename "a"

char djm[1000];

int cases=10;

int mode=1;

int getrand()
{
	return (rand()<<15)+rand();
}

int z[310],y[310*310];

void make_data(int test)
{
	int n,up;
	if (test<=3) n=5,up=10;
	else if (test<=6) n=50,up=100;
	else n=300,up=100000000;
	printf("%d\n",n);
	for (int a=1;a<=n;a++)
		z[a]=getrand()%up+1;
	int m=0;
	for (int a=1;a<=n;a++)
		for (int b=a+1;b<=n;b++)
			y[++m]=z[a]+z[b];
	random_shuffle(y+1,y+m+1);
	for (int a=1;a<=m;a++)
		printf("%d%c",y[a],a==m?'\n':' ');
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
