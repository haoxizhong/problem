#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
 
using namespace std;
 
const int maxn=4001;
const int maxm=2000*2000;
const int INF=123456789;
 
int result[maxn],hehe[maxn],x[maxn],y[maxn],en,A,B,m,ans;
 
bool map[250][maxn],use[maxn],use2[maxn],use3[maxn];
 
queue<int> que;
 
struct edge
{
    int e;
    edge *next;
}*v[maxn],ed[maxm];
 
void add_edge(int s,int e)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}
 
bool check2(int a,int b)
{
    int now=a | b;
    int sum=0;
    while (now)
    {
        if (now % 2==1) sum++;
        now>>=1;
    }
    if (sum % 2==0) return true;
    else return false;
}
 
bool dfs2(int now)
{
    for (edge *e=v[now];e;e=e->next)
        if (!use3[e->e])
        {
            use3[e->e]=true;
            if (result[e->e]==0 || dfs2(result[e->e]))
            {
                result[e->e]=now;
                return true;
            }
        }
    return false;
}
 
void dinic()
{
    int flow=0,cnt2=0;
    for (int a=1;a<=B;a++)
        use2[a]=true;
    for (int a=1;a<=A;a++)
        if (use[a])
        {
            cnt2++;
            for (int b=1;b<=B;b++)
                use2[b]=use2[b] && map[a][b]; 
        }
    int cnt=0;
    for (int a=1;a<=B;a++)
        if (use2[a])
        {
            cnt++;
            hehe[cnt]=a;
        }
    en=0;
    memset(v,0,sizeof(v));
    for (int a=1;a<=cnt;a++)
        if (y[hehe[a]] % 2==1)
        {
            for (int b=1;b<=cnt;b++)
                if (y[hehe[b]] % 2==0) if (check2(y[hehe[a]],y[hehe[b]])) add_edge(a,b);
        }
    memset(result,0,sizeof(result));
    for (int a=1;a<=cnt;a++)
        if (y[hehe[a]] % 2==1)
        {
            memset(use3,false,sizeof(use3));
            if (dfs2(a)) flow++;
        }
    ans=max(ans,cnt-flow+cnt2);
}
 
void get()
{
    dinic();
    for (int a=1;a<=A;a++)
    {
        use[a]=true;
        dinic();
        use[a]=false;
    }
    for (int a=1;a<=A;a++)
        for (int b=a+1;b<=A;b++)
            if ((x[a]+x[b]) % 2==1)
            {
                use[a]=use[b]=true;
                dinic();
                use[a]=use[b]=false;
            }
}
 
int main()
{
    //freopen("friends.in","r",stdin);
    //freopen("friends.out","w",stdout);
 
    int t;
    scanf("%d",&t);
    for (int a=1;a<=t;a++)
    {
        ans=0;
        scanf("%d%d%d",&A,&B,&m);
        for (int b=1;b<=A;b++)
            scanf("%d",&x[b]);
        for (int b=1;b<=B;b++)
            scanf("%d",&y[b]);
        memset(map,false,sizeof(map));
        for (int b=1;b<=m;b++)
        {
            int s,e;
            scanf("%d%d",&s,&e);
            map[s][e]=true;
        }
        get();
        printf("%d\n",ans);
    }
 
    return 0;
}
