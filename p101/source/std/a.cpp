#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

const int maxn=2000;

int n,num[maxn];

char s[maxn];

bool check1(char *s)
{
	int l=strlen(s+1);
	if (l!=n) return false;
	int sum=0;
	for (int a=1;a<=n;a++)
		if (s[a]=='1') sum+=a;
	for (int a=1;a<=n;a++)
	{
		if (s[a]=='1')
		{
			sum-=a;
			if (sum % (n+1)==0)
			{
				s[a]='0';
				printf("%s\n",s+1);
				return true;
			}
			sum+=a;
		}
	}
	return false;
}

bool check2(char *s)
{
	int l=strlen(s+1);
	if (l!=n-1) return false;
	int fs=0;
	for (int a=1;a<=l;a++)
	{
		num[a]=num[a-1];
		if (s[a]=='1') num[a]++,fs+=a;
	}
	for (int a=1;a<=n;a++)
	{
		fs+=num[l]-num[a-1];
		if (fs % (n+1)==0)
		{
			for (int b=1;b<a;b++)
				printf("%c",s[b]);
			printf("0");
			for (int b=a;b<=l;b++)
				printf("%c",s[b]);
			printf("\n");
			return true;
		}
		fs+=a;
		if (fs % (n+1)==0)
		{
			for (int b=1;b<a;b++)
				printf("%c",s[b]);
			printf("1");
			for (int b=a;b<=l;b++)
				printf("%c",s[b]);
			printf("\n");
			return true;
		}
		fs-=a+num[l]-num[a-1];
	}
	return false;
}

bool check3(char *s)
{
	int l=strlen(s+1);
	if (l!=n+1) return false;
	int sum=0;
	for (int a=1;a<=l;a++)
	{
		num[a]=num[a-1];
		if (s[a]=='1') sum+=a,num[a]++;
	}
	for (int a=1;a<=l;a++)
	{
		sum-=num[l]-num[a];
		if (s[a]=='1') sum-=a;
		if (sum % (n+1)==0)
		{
			for (int b=1;b<a;b++)
				printf("%c",s[b]);
			for (int b=a+1;b<=l;b++)
				printf("%c",s[b]);
			printf("\n");
			return true;
		}
		sum+=num[l]-num[a];
		if (s[a]=='1') sum+=a;
	}
	return false;
}

bool check4(char *s)
{
	int l=strlen(s+1);
	if (l!=n) return false;
	int sum=0;
	for (int a=1;a<=l;a++)
		if (s[a]=='1') sum+=a;
	if (sum % (n+1)==0)
	{
		printf("%s\n",s+1);
		return true;
	}
	return false;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);

	scanf("%d",&n);
	while (~scanf("%s",s+1))
	{
		bool able=false;
		able=check4(s);
		if (able) continue;
		able=check1(s);
		if (able) continue;
		able=check2(s);
		if (able) continue;
		able=check3(s);
		if (able) continue;
		printf("-1\n");
	}

	return 0;
}
