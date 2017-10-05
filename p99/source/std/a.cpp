#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<map>

using namespace std;

struct node
{
       int z[30];
       node()
       {
             memset(z,0,sizeof(z));
       }
       bool operator<(const node &a)const
       {
            for (int b=1;b<=26;b++)
            if (z[b]!=a.z[b]) return z[b]<a.z[b];
            return false;
       }
}now;

map<node,bool> use;

int ans,n;

char s[120];

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
    scanf("%d",&n);
    for (int a=1;a<=n;a++)
    {
        scanf("%s",s+1);
        int l=strlen(s+1);
        memset(now.z,0,sizeof(now.z));
        for (int a=1;a<=l;a++)
            now.z[s[a]-'A'+1]++;
        if (!use[now]) use[now]=true,ans++;
    }
    printf("%d\n",ans);
    
    return 0;
}
