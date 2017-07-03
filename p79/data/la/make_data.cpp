#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;

#define problem "la"
#define prename "c"

char djm[1000];

int cases=10;

int mode=1;

bool use[100000];

void make_data(int test)
{
	int n,k;
	k=536870911;
	if (test==1) n=1;
	if (test==2) n=20;
	if (test==3) n=50;
	if (test==4) n=100;
	if (test==5) n=300;
	if (test==6) n=350;
	if (test==7) n=400;
	if (test==8) n=450;
	if (test==9) n=500;
	if (test==10) n=500;
	memset(use,false,sizeof(use));
	printf("%d %d\n",n,k);
	for (int a=1;a<=n;a++)
		for (int b=1;b<=n;b++)
			if (a>b) printf("%d ",0);
			else
			{
				if (a==b)
				{
					int x=rand()+1;
					while (use[x]) x=rand()+1;
					use[x]=true;
					printf("%d ",x);
				}
				else printf("%d ",rand()+1);
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
