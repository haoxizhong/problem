#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

#define problem "Q"
#define prename "J"

char djm[1000];

int z[100010];

int cases=10;

int mode=2;

int getrand()
{
	return (rand()<<16)+rand();
}

void make_data(int test)
{
	int t=10;
	printf("%d\n",t);
	for (;t--;)
	{
		int n=rand()%66+1,m=rand()%6+1;
		printf("%d %d\n",n,m);
		for (int a=1;a<=n;a++)
			for (int b=1;b<=m;b++)
			{
				int t=rand()%8,v;
				if (!t)
				{
					int upper=4;
					if (a==1) upper--;
					if (a==n) upper--;
					if (b==1) upper--;
					if (b==m) upper--;
					v=rand()%upper+1;
				}
				else v=-1;
				printf("%d",v);
				if (b==m) printf("\n");
				else printf(" ");
			}
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
