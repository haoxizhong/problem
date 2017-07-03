#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>

using namespace std;

const int maxk=2010;

char djm[30];

struct point
{
	int x,y;
	point(){}
	point(int a,int b)
	{
		x=a;y=b;
	}
	void init()
	{
		scanf("%d%d",&x,&y);
	}
	bool operator<(const point &a)const
	{
		if (x!=a.x) return x<a.x;
		else return y<a.y;
	}
	bool operator==(const point &a)const
	{
		return x==a.x && y==a.y;
	}
}p[maxk];

int getrand()
{
	return rand();
}

int main()
{
	for (int test=1;test<=20;test++)
	{
		fprintf(stderr,"%d\n",test);
		sprintf(djm,"square%d.in",test);
		freopen(djm,"w",stdout);

		int n=getrand()%500000+500000,m=getrand()%500000+500000,k=getrand()%500+1500;
		if (test<=12 && test>=11) n=getrand()%500+500,m=getrand()%500+500;
		if (test<=10) k=getrand()%100+100;
		if (test<=8) k=getrand()%25+25;
		if (test<=6) k=0;
		if (test<=4) n=getrand()%25+25,m=getrand()%25+25,k=getrand()%25+25;
		if (test<=2) n=getrand()%5+1,m=getrand()%5+1,k=getrand()%(n*m+1);
		for (int a=1;a<=k;)
		{
			int x,y,dx,dy;
			int px[4],py[4];
			do
			{
				x=getrand()%(n+1);
				y=getrand()%(m+1);
				dx=getrand()%(n+1)*(getrand()%2?-1:1);
				dy=getrand()%(n+1)*(getrand()%2?-1:1);
				bool able=true;
				if (!dx && !dy) able=false;
				for (int b=0;b<4;b++)
				{
					px[b]=x;py[b]=y;
					x+=dx;y+=dy;
					swap(dx,dy);
					dx=-dx;
					if (px[b]<0 || px[b]>n || py[b]<0 || py[b]>m) able=false;
				}
				if (able) break;
			}while (true);
			for (int b=0;b<4;b++)
				if (getrand()%2 && a<=k) p[a++]=point(px[b],py[b]);
		}
		sort(p+1,p+k+1);
		k=unique(p+1,p+k+1)-p-1;
		random_shuffle(p+1,p+k+1);
		printf("%d %d %d\n",n,m,k);
		for (int a=1;a<=k;a++)
			printf("%d %d\n",p[a].x,p[a].y);

		fclose(stdout);

		sprintf(djm,"./std < square%d.in > square%d.ans",test,test);
		system(djm);
	}

	return 0;
}
