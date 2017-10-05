#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

char s[1000],z[1000];

int size;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	scanf("%s",s+1);
	int l=strlen(s+1);
	size++;
	z[size]=s[1];
	for (int a=2;a<=l;a++)
	{
		if (s[a]==')')
		{
			if (z[size]!='(')
			{
				printf("Wrong\n");
				return 0;
			}
			else size--;
		}
		if (s[a]==']')
		{
			if (z[size]!='[')
			{
				printf("Wrong\n");
				return 0;
			}
			else size--;
		}
		if (s[a]=='}')
		{
			if (z[size]!='{')
			{
				printf("Wrong\n");
				return 0;
			}
			else size--;
		}
		if (s[a]=='(' || s[a]=='[' || s[a]=='{')
		{
			size++;
			z[size]=s[a];
		}
	}
	if (size!=0) printf("Wrong\n");
	else printf("OK\n");

	return 0;
}
