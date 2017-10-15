#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

char djm[10000];

int getrand()
{
	return (rand()<<16)+rand();
}

int main()
{
	srand(19960618);
	for (int a=7;a<=10;a++)
	{
		sprintf(djm,"wosa%d.in",a);
		freopen(djm,"w",stdout);

		int n=rand()%250+250;
		if (a<=3) n=20;
		printf("%d\n",n);
		for (int b=1;b<=n;b++)
		{
			int opt=rand()%4+1;
			if (opt==1) printf("Goalkeeper ");
			if (opt==2) printf("Defender ");
			if (opt==3) printf("Midfielder ");
			if (opt==4) printf("Forward ");
			if (a==1) printf("0 %d\n",rand()%30);
			else
			{
				if (a<=3) printf("%d %d\n",rand()%30,rand()%30);
				else
				{
					if (a<=6) printf("%d %d\n",rand()%5+5,rand()%5+5);
					else printf("%d %d\n",rand()%(12-a)+80,rand()%(12-a)+80);
				}
			}
		}
		if (a<=3) printf("%d\n",rand()%300);
		else
		{
			if (a<=6) printf("1000\n");
			else printf("%d\n",rand()%100+900);
		}

		fclose(stdout);

		sprintf(djm,"wosa.exe < wosa%d.in > wosa%d.out",a,a);
		system(djm);

		fprintf(stderr,"%d",a);
	}

	return 0;
}
