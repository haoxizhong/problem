#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

const int maxn=200;
const long long mo=1000000007;
const long long mo2=mo*2+2;
const long long mo3=mo2*3;

char s[maxn];

struct matrix
{
	long long z[3][3];
	matrix()
	{
		memset(z,0,sizeof(z));
	}
	matrix operator*(const matrix &a)const
	{
		matrix ans;
		for (int b=1;b<=2;b++)
			for (int c=1;c<=2;c++)
				for (int d=1;d<=2;d++)
					ans.z[b][c]=(ans.z[b][c]+z[b][d]*a.z[d][c]%mo)%mo;
		return ans;
	}
	matrix operator+(const matrix &a)const
	{
		matrix ans;
		for (int b=1;b<=2;b++)
			for (int c=1;c<=2;c++)
				for (int d=1;d<=2;d++)
					ans.z[b][c]=(ans.z[b][c]+z[b][d]*a.z[d][c]%mo2)%mo2;
		return ans;
	}
}m1,m2;

struct bign
{
	int z[maxn],l;
	void init()
	{
		memset(z,0,sizeof(z));
		scanf("%s",s+1);
		l=strlen(s+1);
		for (int a=1;a<=l;a++)
			z[a]=s[l-a+1]-'0';
	}
	long long operator%(const long long &a)const
	{
		long long b=0;
		for (int c=l;c>=1;c--)
			b=(b*10+z[c])%a;
		return b;
	}
}z;

long long get(long long v)
{
	if (v==0) return 0;
	m1.z[1][1]=0;
	m1.z[1][2]=1;
	m2.z[1][1]=0;
	m2.z[1][2]=m2.z[2][1]=m2.z[2][2]=1;
	while (v)
	{
		if (v&1) m1=m1*m2;
		m2=m2*m2;
		v>>=1;
	}
	return m1.z[1][1];
}

long long get1(long long v)
{
	if (v==0) return 0;
	m1.z[1][1]=0;
	m1.z[1][2]=1;
	m2.z[1][1]=0;
	m2.z[1][2]=m2.z[2][1]=m2.z[2][2]=1;
	while (v)
	{
		if (v&1) m1=m1+m2;
		m2=m2+m2;
		v>>=1;
	}
	return m1.z[1][1];
}

int main()
{
	freopen("na.in","r",stdin);
	freopen("na.out","w",stdout);

	int t;
	scanf("%d",&t);
	for (int a=1;a<=t;a++)
	{
		z.init();
		long long v1=z % mo3;
		v1=get1(v1);
		printf(LL "\n",get(v1));
	}

    return 0;
}

