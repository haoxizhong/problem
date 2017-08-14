#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

int l,k;

char s1[110],s2[20];

int main()
{
	scanf("%d%d",&l,&k);
	scanf("%s%s",s1,s2);
	for (int a=0;a<l;a++)
		putchar((s1[a]-'a'+s2[a%k]-'0')%26+'a');
	putchar('\n');

	return 0;
}
