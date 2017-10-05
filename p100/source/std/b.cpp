#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
using namespace std;
int a,b,l;
double get(double v1)
{
    double v2=sqrt(l*l-v1*v1);
    if (a*v1+b*v2<v1*v2) return -1e+20;
    else return (a*v1+b*v2-v1*v2)/l;
}
int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
    scanf("%d%d%d",&a,&b,&l);
    if (a>=l && b>=l) printf("%d.0000000\n",l);
    else
    {
        if (a>=l) printf("%d.0000000\n",b);
        else
        {
            if (b>=l) printf("%d.0000000\n",a);
            else
            {
                double lv=0.0,rv=l;
                for (int c=1;c<=100;c++)
                {
                    double m1=(rv-lv)/3.0+lv;
                    double m2=lv+rv-m1;
                    if (get(m1)<0.0 || get(m2)<0.0)
                    {
                        printf("My poor head =(\n");
                        return 0;
                    }
                    if (get(m1)<get(m2)) rv=m2;
                    else lv=m1;
                }
                printf("%.7lf\n",get(rv));
            }
        }
    }
    return 0;
}
