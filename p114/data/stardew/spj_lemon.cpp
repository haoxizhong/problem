#include "testlib.h"
#include <tgmath.h>

const int maxn=50000;
const int maxp=1000000;
const long double eps=1e-4;

long double ans_value[11];

int sgn(long double x)
{
	if (fabsl(x)<=eps) return 0;
	if (x>0) return 1;
	else return -1;
}

struct point
{
	long double x,y;
	void init(InStream &fin)
	{
		x=fin.readDouble();
		y=fin.readDouble();
	}
	bool operator==(const point &a)const
	{
		return sgn(x-a.x)==0 && sgn(y-a.y)==0;
	}
	bool operator!=(const point &a)const
	{
		return sgn(x-a.x)!=0 || sgn(y-a.y)!=0;
	}
}output_point[maxp];

struct segment
{
	point p1,p2;
	long double angle;
	void init(InStream &fin)
	{
		p1.init(fin);
		p2.init(fin);
		angle=atan2l(p2.y-p1.y,p2.x-p1.x);
	}
	void init(point pp1,point pp2)
	{
		p1=pp1;
		p2=pp2;
		angle=atan2l(p2.y-p1.y,p2.x-p1.x);
	}
	bool operator<(const segment &a)const
	{
		return angle<a.angle;
	}
	long double calc_dist()
	{
		return sqrtl((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	}
	void print()
	{
		//printf("%lf %lf %lf %lf\n",(double)p1.x,(double)p1.y,(double)p2.x,(double)p2.y);
	}
}seg[maxn+maxp],output_seg[maxp+10];

struct interval
{
	long double l,r;
	bool operator<(const interval &a)const
	{
		return sgn(l-a.l)<0;
	}
	void init(long double v1,long double v2)
	{
		l=v1;r=v2;
		if (sgn(l-r)>0) std::swap(l,r);
	}
}inte[maxp+10];

bool another_check(int n,long double l,long double r)
{
	std::sort(inte+1,inte+n+1);
	long double nowr=l;
	for (int a=1;a<=n;a++)
	{
		if (sgn(inte[a].r-l)<=0 || sgn(inte[a].l-r)>=0) continue;
		if (sgn(inte[a].l-nowr)>0) return false;
		nowr=std::max(nowr,std::min(inte[a].r,r));
	}
	return sgn(nowr-r)==0;
}

bool check(int num,int left,int right)
{
	int cnt=0;
	for (int a=left;a<right;a++)
		inte[++cnt].init(output_seg[a].p1.x,output_seg[a].p2.x);
	long double nowl=seg[num].p1.x,nowr=seg[num].p2.x;
	if (sgn(nowl-nowr)>0) std::swap(nowl,nowr);
	if (!another_check(cnt,nowl,nowr)) return false;
	
	cnt=0;
	for (int a=left;a<right;a++)
		inte[++cnt].init(output_seg[a].p1.y,output_seg[a].p2.y);
	nowl=seg[num].p1.y,nowr=seg[num].p2.y;
	if (sgn(nowl-nowr)>0) std::swap(nowl,nowr);
	if (!another_check(cnt,nowl,nowr)) return false;

	return true;
}

bool cmp(segment s1,segment s2)
{
	return s1.p1.x<s2.p1.x;
}

void score(int s,char *n)
{
	FILE *f=fopen(n,"w");
	fprintf(f,"%d\n",s);
	fclose(f);
}

void infx(char *s,char *n)
{
	FILE *f=fopen(n,"w");
	fprintf(f,"%s\n",s);
	fclose(f);
}

int main(int argc,char *argv[])
{
	setName("It's the checker for Stardew!");
	registerTestlibCmd(4,argv);

	//Read .in
	int n=inf.readInt();
	for (int a=1;a<=n;a++)
		seg[a].init(inf);

	//Read .out
	int m=ouf.readInt();
	if (m>5*n*n || m>1000000) 
	{
		score(0,argv[5]);
		infx("Yout path contains too many points!",argv[6]);
		quitf(_ok,"");
	}
	for (int a=0;a<m;a++)
		output_point[a].init(ouf);

	//Read .ans
	for (int a=1;a<=10;a++)
		ans_value[a]=ans.readDouble();

	for (int a=1;a<m;a++)
		output_seg[a].init(output_point[a-1],output_point[a]);
	output_seg[m].init(output_point[m-1],output_point[0]);
	std::sort(seg+1,seg+n+1);
	std::sort(output_seg+1,output_seg+m+1);
	for (int a=1,b=1;a<=n;a++)
	{	
		while (b<=m && sgn(output_seg[b].angle-seg[a].angle)<0)
			b++;
		if (sgn(output_seg[b].angle-seg[a].angle)!=0) 
		{
			score(0,argv[5]);
			infx("Your path doesn't cover all the segments!",argv[6]);
			quitf(_ok,"");
		}
		int c=b;
		while (c<=m && sgn(output_seg[b].angle-output_seg[c].angle)==0)
			c++;
		if (!check(a,b,c)) 
		{
			//seg[a].print();
			//std::sort(output_seg+b,output_seg+c,cmp);
			//for (int d=b;d<c;d++)
			//	output_seg[d].print();
			score(0,argv[5]);
			infx("Your path doesn't cover all the segments!",argv[6]);
			quitf(_ok,"");
		}
	}

	//Calculate the answer
	long double dist=0;
	for (int a=1;a<=m;a++)
		dist+=output_seg[a].calc_dist();
	int scores=1;
	for (int a=1;a<=10;a++)
		if (sgn(dist-ans_value[a])<=0) scores=a;

	//quitp((double)score/10,"You get %d score! Your answer is %lf",score,(double)dist);

	score(scores,argv[5]);
	char s[100];
	sprintf(s,"Niubi! Your value is %lf",(double)dist);
	infx(s,argv[6]);
	quitf(_ok,"");
}
