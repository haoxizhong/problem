#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

char djm[100];

int main()
{
	for (int a=1;a<=100;a++)
	{
		sprintf(djm,"a.exe < %d.in > %d.out",a,a);
		system(djm);
		printf("%d\n",a);
	}

	return 0;
}
