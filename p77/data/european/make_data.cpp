#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "european"
#define prename "c"

char djm[1000];

int z[100010];

int cases=10;

int mode=1;

int getrand()
{
	return (rand()<<16)+rand();
}

void make_data(int test)
{
	int n=getrand()%50000+50000;
	printf("%d\n",n);
	int sum=0;
	for (int a=1;a<n;a++)
	{
		int v=0;
		while (!v)
		{
			int l=max(-100,-100-sum);
			int r=min(100,100-sum);
			v=rand()%(r-l+1)+l;
			z[a]=v;
		}
		sum+=v;
	}
	z[n]=-sum;
	random_shuffle(z+1,z+n+1);
	for (int a=1;a<=n;a++)
	{
		printf("%d",z[a]);
		if (a==n) printf("\n");
		else printf(" ");
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
