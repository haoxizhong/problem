#include<cstdio>
#include<cstdlib>
#include<cstring>
 
using namespace std;
 
const int maxn=1000010;
 
char s[maxn];
 
int main()
{
	freopen("shower.in","r",stdin);
	freopen("shower.out","w",stdout);

    scanf("%s",s+1);
    int l=strlen(s+1),ans=0,v=0;
    for (int a=1;a<=l;a++)
    {
        if (s[a]=='(') v++;
        else v--;
        if (v<0) v=1,ans++;
    }
    printf("%d\n",ans+(v>>1));
 
    return 0;
}
