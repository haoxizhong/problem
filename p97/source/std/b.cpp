#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double eps=1e-8;
int sgn(double a)
{
    if (fabs(a)<eps) return 0;
    else
    {
        if (a>0.0) return 1;
        else return -1;
    }
}
struct point
{
    double x,y;
    point(){}
    point(double a,double b)
    {
        x=a;y=b;
    }
    void init()
    {
        scanf("%lf%lf",&x,&y);
    }
    point operator+(const point &a)const
    {
        point ans;
        ans.x=x+a.x;
        ans.y=y+a.y;
        return ans;
    }
    point operator-(const point &a)const
    {
        point ans;
        ans.x=x-a.x;
        ans.y=y-a.y;
        return ans;
    }
    point operator*(const double &a)const
    {
        point ans;
        ans.x=x*a;
        ans.y=y*a;
        return ans;
    }
    void print()
    {
        printf("%lf %lf\n",x,y);
    }
}v,p,w1,w2,m1,m2;
double cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
double dot(point a,point b)
{
    return a.x*b.x+a.y*b.y;
}
bool cross(point p1,point p2,point p3,point p4)
{
    if (sgn(cross(p2-p1,p3-p1))*sgn(cross(p2-p1,p4-p1))==1) return false;
    if (sgn(cross(p4-p3,p1-p3))*sgn(cross(p4-p3,p2-p3))==1) return false;
    if (sgn(max(p1.x,p2.x)-min(p3.x,p4.x))==-1) return false;
    if (sgn(max(p1.y,p2.y)-min(p3.y,p4.y))==-1) return false;
    if (sgn(max(p3.x,p4.x)-min(p1.x,p2.x))==-1) return false;
    if (sgn(max(p3.y,p4.y)-min(p1.y,p2.y))==-1) return false;
    return true;
}
point getcross(point p1,point p2,point p3,point p4)
{
    double a=p2.y-p1.y;
    double b=p1.x-p2.x;
    double c=-p1.x*p2.y+p1.y*p2.x;
    double d=p4.y-p3.y;
    double e=p3.x-p4.x;
    double f=-p3.x*p4.y+p3.y*p4.x;
    double x=(b*f-c*e)/(a*e-b*d);
    double y=(a*f-c*d)/(b*d-a*e);
    return point(x,y);
}
point calcfoot(point p1,point p2,point p3)
{
    double ratio=dot(p1-p2,p3-p2)/dot(p3-p2,p3-p2);
    return p2+(p3-p2)*ratio;
}
bool check()
{
    if (!cross(v,p,w1,w2))
    {
        if (!cross(v,p,m1,m2)) return true;
        if (sgn(cross(m1-v,m2-v))==0 && sgn(cross(m1-p,m2-p)==0)) return true;      
    }
    if (sgn(cross(m2-m1,v-m1))*sgn(cross(m2-m1,p-m1))==1)
    {
        point foot=calcfoot(p,m1,m2);
        foot=foot*2.0-p;
        if (cross(v,foot,m1,m2))
        {
            foot=getcross(v,foot,m1,m2);
            if (!cross(v,foot,w1,w2) && !cross(foot,p,w1,w2)) return true;
        }
    }
    return false;
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
    v.init();
    p.init();
    w1.init();
    w2.init();
    m1.init();
    m2.init();
    if (check()) printf("YES\n");
    else printf("NO\n");
    return 0;
}
