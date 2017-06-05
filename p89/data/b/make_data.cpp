#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>

using namespace std;

#define problem "b"
#define prename "c"

char djm[1000];

int cases=10;

int mode=1;

const double eps=1e-5;

int n,m;

int sgn(double x)
{
	if (fabs(x)<=eps) return 0;
	if (x>0) return 1;
	else return -1;
}

struct segment
{
	double x1,y1,x2,y2;
	int dir;
	void init(double x1,double y1,double x2,double y2)
	{
		this->x1=x1;this->y1=y1;this->x2=x2;this->y2=y2;
		if (sgn(y1-y2)==0) 
		{
			dir=0;
			if (sgn(x1-x2)>0) swap(x1,x2);
		}
		else 
		{
			dir=1;
			if (sgn(y1-y2)>0) swap(y1,y2);
		}
	}
	bool operator==(const segment &a)const
	{
		return dir==a.dir && sgn(x1-a.x1)==0 && sgn(x2-a.x2)==0  && sgn(y1-a.y1)==0 && sgn(y2-a.y2)==0;
	}
	double len()
	{
		return fabs(x2-x1)+fabs(y2-y1);
	}
	void output()
	{
		printf("%.3lf %.3lf %.3lf %.3lf\n",x1,y1,x2,y2);
	}
	void delta(double dx,double dy,double ratio)
	{
		x1=x1*ratio+dx;
		x2=x2*ratio+dx;
		y1=y1*ratio+dy;
		y2=y2*ratio+dy;
	}
}seg_n[100],seg_m[100];

void gen_seg(int id)
{
	int dir=rand()%2;
	int x1,y1,x2,y2;
	x1=rand()%1001-500;
	y1=rand()%1001-500;
	if (dir==0) x2=x1,y2=rand()%1001-500;
	else x2=rand()%1001-500,y2=y1;
	seg_m[id].init(x1,y1,x2,y2);
}

bool cro(segment a,segment b)
{
	if (a.dir) swap(a,b);
	if (sgn(b.y1-a.y1)>=0 || sgn(a.y1-b.y2)>=0) return false;
	if (sgn(a.x1-b.x1)>=0 || sgn(b.x1-a.x2)>=0) return false;
	return true;
}

bool cover(segment a,segment b)
{
	if (a.dir==0 && b.dir==0 && fabs(a.y1-b.y1)==0)
	{
		double l=a.x1;
		double r=a.x2;
		if (sgn(b.x1-l)>=0 && sgn(b.x1-r)<=0) return true;
		if (sgn(b.x2-l)>=0 && sgn(b.x2-r)<=0) return true;
	}
	if (a.dir==1 && b.dir==1 && fabs(a.x1-b.x1)==0)
	{
		double l=a.y1;
		double r=a.y2;
		if (sgn(b.y1-l)>=0 && sgn(b.y1-r)<=0) return true;
		if (sgn(b.y2-l)>=0 && sgn(b.y2-r)<=0) return true;
	}
	return false;
}

bool check_able()
{
	for (int a=1;a<=m;a++)
		if (sgn(seg_m[a].len())==0) return false;
	for (int a=1;a<=m;a++)
		for (int b=a+1;b<=m;b++)
			if (cover(seg_m[a],seg_m[b])) return false;
	return true;
}

bool check_intersection(segment *z,int n)
{
	for (int a=1;a<=n;a++)
		for (int b=a+1;b<=n;b++)
			if (z[a].dir!=z[b].dir)
			{
				if (cro(z[a],z[b])) return true;
			}
	return false;
}

void gen_block()
{
	while (true)
	{
		double x1=0,x2=0,y1=0,y2=0;
		while (x1==x2 || y1==y2)
		{
			x1=rand()%1001-500;
			x2=rand()%1001-500;
			y1=rand()%1001-500;
			y2=rand()%1001-500;
		}
		if (x1>x2) swap(x1,x2);
		if (y1>y2) swap(y1,y2);
		n=0;
		for (int a=1;a<=m;a++)
			if (seg_m[a].dir==0)
			{
				double xx1=seg_m[a].x1,xx2=seg_m[a].x2,y=seg_m[a].y1;
				if (xx1>xx2) swap(xx1,xx2);
				if (sgn(y-y1)>=0 && sgn(y-y2)<=0)
				{
					double l=max(xx1,x1),r=min(x2,xx2);
					if (sgn(l-r)<=0)
					{
						n++;
						seg_n[n].init(l,y,r,y);
					}
				}
			}
			else
			{
				double yy1=seg_m[a].y1,yy2=seg_m[a].y2,x=seg_m[a].x1;
				if (yy1>yy2) swap(yy1,yy2);
				if (sgn(x-x1)>=0 && sgn(x-x2)<=0)
				{
					double l=max(yy1,y1),r=min(y2,yy2);
					if (sgn(l-r)<=0)
					{
						n++;
						seg_n[n].init(x,l,x,r);
					}
				}
			}
		bool able=true;
		for (int a=1;a<=n;a++)
		{
			if (sgn(seg_n[a].len())==0) able=false;
			if (seg_n[a].dir==0)
			{
				if (sgn(seg_n[a].y1-y1)==0) able=false;
				if (sgn(seg_n[a].y1-y2)==0) able=false;
			}
			else
			{
				if (sgn(seg_n[a].x1-x1)==0) able=false;
				if (sgn(seg_n[a].x1-x2)==0) able=false;
			}
		}
		if (able && check_intersection(seg_n,n)) break;
	}
	/*double dx=(double)rand()/RAND_MAX*1001-500;
	double dy=(double)rand()/RAND_MAX*1001-500;
	double ratio=(double)rand()/RAND_MAX*20+2;
	for (int a=1;a<=n;a++)
		seg_n[a].delta(dx,dy,ratio);*/
}

void make_data(int test)
{
	int t=10;
	for (int g=1;g<=t;g++)
	{
		while (true)
		{
			m=rand()%25+25;
			if (test<=4) m=rand()%10+10;
			if (test<=2) m=rand()%3+1;
				for (int a=1;a<=m;a++)
					gen_seg(a);
			if (!check_able()) continue;
			if (check_intersection(seg_m,m)) break;
		}
		gen_block();
		if (g%test!=0)
		{
			n++;
			int dir=rand()%2;
			int x1,y1,x2,y2;
			x1=rand()%1001-500;
			y1=rand()%1001-500;
			if (dir==0) x2=x1,y2=rand()%1001-500;
			else x2=rand()%1001-500,y2=y1;
			seg_n[n].init(x1,y1,x2,y2);
		}
		printf("%d %d\n",n,m);
		for (int a=1;a<=n;a++)
			seg_n[a].output();
		for (int a=1;a<=m;a++)
			seg_m[a].output();
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
