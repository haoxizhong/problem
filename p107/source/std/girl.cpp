#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
 
using namespace std;

const int BUF_SIZE = 30;
char buf[BUF_SIZE], *buf_s = buf, *buf_t = buf + 1;
  
#define PTR_NEXT() \
    { \
        buf_s ++; \
        if (buf_s == buf_t) \
        { \
            buf_s = buf; \
            buf_t = buf + fread(buf, 1, BUF_SIZE, stdin); \
        } \
    }
   
#define readint(_n_) \
    { \
        while (*buf_s != '-' && !isdigit(*buf_s)) \
            PTR_NEXT(); \
        bool register _nega_ = false; \
        if (*buf_s == '-') \
        { \
            _nega_ = true; \
            PTR_NEXT(); \
        } \
        int register _x_ = 0; \
        while (isdigit(*buf_s)) \
        { \
            _x_ = _x_ * 10 + *buf_s - '0'; \
            PTR_NEXT(); \
        } \
        if (_nega_) \
            _x_ = -_x_; \
        (_n_) = (_x_); \
    }
 
const int maxn=100010;
const int mo=1000000007;
 
int n,m,en,size;
 
bool vis[maxn],circle;
 
struct edge
{
    int e;
    edge *next;
}*v[maxn],ed[maxn<<1];
 
void add_edge(int s,int e)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}
 
void dfs(int now,int pre)
{
    vis[now]=true;
    size++;
    for (edge *e=v[now];e;e=e->next)
        if (e->e!=pre)
        {
            if (vis[e->e]) circle=true;
            else dfs(e->e,now);
        }
}
 
int main()
{
	freopen("girl.in","r",stdin);
	freopen("girl.out","w",stdout);
 
	readint(n);
	readint(m);
    for (;m--;)
    {
        int s,e;
		readint(s);
		readint(e);
        add_edge(s,e);
        add_edge(e,s);
    }
    int ans=1;
    for (int a=1;a<=n;a++)
        if (!vis[a])
        {
            circle=false;
            size=0;
            dfs(a,0);
            if (circle) ans=(ans<<1)%mo;
            else ans=(long long)ans*size%mo;
        }
    printf("%d\n",ans);
 
    return 0;
}
