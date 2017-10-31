#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>

using namespace std;

const int mo=1000000007;
const int maxn=100;

int n,id1[maxn],id2[maxn],l[maxn],res[maxn];

long long num1[maxn],num2[maxn],size[maxn];

struct rec
{
	int p;
	long long p1,p2;
	rec(){}
	rec(int a,long long b,long long c)
	{
		p=a;
		if (b<c) p1=b,p2=c;
		else p1=c,p2=b;
	}
	bool operator<(const rec &a)const
	{
		if (p!=a.p) return p<a.p;
		if (p1!=a.p1) return p1<a.p1;
		return p2<a.p2;
	}
};

map< pair<int,long long > ,int > ma;

map<rec,int> ma2;

int solve(int p,long long p1,long long p2)
{
	if (!p) return 0;
	if (p1==p2) return 0;
	rec x=rec(p,p1,p2);
	if (ma2.count(x)) return ma2[x];
	if (p1<size[id1[p]])
	{
		if (p2<size[id1[p]]) ma2[x]=solve(id1[p],p1,p2);
		else ma2[x]=((long long)solve(id1[p],num1[p],p1)+solve(id2[p],num2[p],p2-size[id1[p]])+l[p])%mo;
	}
	else
	{
		if (p2<size[id1[p]]) ma2[x]=((long long)solve(id1[p],num1[p],p2)+solve(id2[p],num2[p],p1-size[id1[p]])+l[p])%mo;
		else ma2[x]=solve(id2[p],p1-size[id1[p]],p2-size[id1[p]]);
	}
	return ma2[x];
}

int solve(int p,long long n)
{
	if (p==0) return 0;
	pair<int,long long> px;
	px=make_pair(p,n);
	if (ma.count(make_pair(p,n))) return ma[px];
	if (n<size[id1[p]]) ma[px]=(((long long)solve(id1[p],num1[p],n)+l[p])*(size[id2[p]]%mo)%mo+solve(id2[p],num2[p])+solve(id1[p],n))%mo;
	else ma[px]=(((long long)solve(id2[p],num2[p],n-size[id1[p]])+l[p])*(size[id1[p]]%mo)%mo+solve(id1[p],num1[p])+solve(id2[p],n-size[id1[p]]))%mo;
	return ma[px];
}

int main()
{
	freopen("cloth.in","r",stdin);
	freopen("cloth.out","w",stdout);

	while (~scanf("%d",&n))
	{
		ma.clear();
		ma2.clear();
		for (int a=1;a<=n;a++)
			scanf("%d%d%I64d%I64d%d",&id1[a],&id2[a],&num1[a],&num2[a],&l[a]);
		size[0]=1;
		for (int a=1;a<=n;a++)
			size[a]=size[id1[a]]+size[id2[a]];
		for (int a=1;a<=n;a++)
			res[a]=((long long)solve(id1[a],num1[a])*(size[id2[a]]%mo)%mo+(long long)(size[id1[a]]%mo)*(size[id2[a]]%mo)%mo*l[a]%mo+(long long)solve(id2[a],num2[a])*(size[id1[a]]%mo)%mo+res[id1[a]]+res[id2[a]])%mo;
		for (int a=1;a<=n;a++)
			printf("%d\n",res[a]);
	}

	return 0;
}
