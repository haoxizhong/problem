#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "valley"
#define prename "a"

char djm[1000];

int cases=10;

int mode=1;

int getrand()
{
	return (rand()<<15)+rand();
}

double randf() {
	return (rand()%100+(double)rand()/RAND_MAX)*(rand()%2?1:-1);
}

void make_data(int test)
{
	int n,m;
	if (test<=2) n=100,m=100;
	else n=50000,m=50000;
	printf("%d %d\n",n,m);
	for (int a=1;a<=n;a++)
	{
		int op=rand()%2+1;
		if (test>=3 && test<=4) op=1;
		if (test==5) op=2;
		if (op==1) printf("1 %.5lf %.5lf\n",randf(),randf());
		else {
			double angle=randf();
			if (test==6) angle=45;
			if (test==7) angle=30;
			printf("2 %.5lf\n",angle);
		}
	}
	for (int a=1;a<=m;a++)
	{
		int l=getrand()%n+1,r=getrand()%n+1;
		if (l>r) swap(l,r);
		printf("%d %d\n",l,r);
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
