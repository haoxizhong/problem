#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cctype>
#include<iostream>
 
using namespace std;

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
 
const int maxn=100010;
const int maxm=600010;
const int INF=1234567899;
 
int ff[maxn],f[maxn][20][3],en,depth[maxn],n,m;
 
queue<int> que;
 
long long sum,ans;
 
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
 
struct leo
{
    int s,e,d;
    bool mst;
    void init()
    {
        readint(s);
        readint(e);
        readint(d);
        mst=false;
    }
    bool operator<(const leo &a)const
    {
        return d<a.d;
    }
}e[maxm];
 
struct edge
{
    int e,d;
    edge *next;
}*v[maxn],ed[maxm];
 
void add_edge(int s,int e,int d)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;v[s]->d=d;
}
 
int getf(int now)
{
    if (ff[now]==now) return now;
    else return ff[now]=getf(ff[now]);
}
 
void bfs()
{
    que.push(1);
    depth[1]=1;
    while (que.size())
    {
        int now=que.front();
        que.pop();
        for (edge *e=v[now];e;e=e->next)
            if (!depth[e->e])
            {
                depth[e->e]=depth[now]+1;
                f[e->e][0][0]=now;
                f[e->e][0][1]=e->d;
                f[e->e][0][2]=-INF;
                int ff=now;
                int o_o=0;
                while (f[ff][o_o][0])
                {
                    f[e->e][o_o+1][0]=f[ff][o_o][0];
                    f[e->e][o_o+1][1]=max(f[ff][o_o][1],f[e->e][o_o][1]);
                    f[e->e][o_o+1][2]=max((f[ff][o_o][1]==f[e->e][o_o+1][1]) ? -INF : f[ff][o_o][1],max((f[ff][o_o][2]==f[e->e][o_o+1][1]) ? -INF : f[ff][o_o][2],max((f[e->e][o_o][1]==f[e->e][o_o+1][1]) ? -INF : f[e->e][o_o][1],(f[e->e][o_o][2]==f[e->e][o_o+1][1]) ? -INF : f[e->e][o_o][2])));
                    ff=f[ff][o_o][0];
                    o_o++;
                }
                que.push(e->e);
            }
    }
}
 
long long getans(int s,int e,int v)
{
    int v1=-INF,v2=-INF;
    if (depth[s]<depth[e]) swap(s,e);
    int delta=depth[s]-depth[e];
    int now=0;
    while (delta)
    {
        if (delta & 1)
        {
            if (f[s][now][1]>v1)
            {
                v2=v1;
                v1=f[s][now][1];
            }
            else
            {
                if (f[s][now][1]>v2 && f[s][now][1]<v1) v2=f[s][now][1];
            }
            if (f[s][now][2]>v1)
            {
                v2=v1;
                v1=f[s][now][2];
            }
            else
            {
                if (f[s][now][2]>v2 && f[s][now][2]<v1) v2=f[s][now][2];
            }
            s=f[s][now][0];
        }
        now++;
        delta>>=1;
    }
    now=0;
    while (s!=e)
    {
        if (now==0 || f[s][now][0]!=f[e][now][0])
        {
            if (f[s][now][1]>v1)
            {
                v2=v1;
                v1=f[s][now][1];
            }
            else
            {
                if (f[s][now][1]>v2 && f[s][now][1]<v1) v2=f[s][now][1];
            }
            if (f[s][now][2]>v1)
            {
                v2=v1;
                v1=f[s][now][2];
            }
            else
            {
                if (f[s][now][2]>v2 && f[s][now][2]<v1) v2=f[s][now][2];
            }
            swap(s,e);
            if (f[s][now][1]>v1)
            {
                v2=v1;
                v1=f[s][now][1];
            }
            else
            {
                if (f[s][now][1]>v2 && f[s][now][1]<v1) v2=f[s][now][1];
            }
            if (f[s][now][2]>v1)
            {
                v2=v1;
                v1=f[s][now][2];
            }
            else
            {
                if (f[s][now][2]>v2 && f[s][now][2]<v1) v2=f[s][now][2];
            }
            swap(s,e);
            s=f[s][now][0];
            e=f[e][now][0];
            now++;
        }
        else now--;
    }
    if (v1==INF) return 123456789876543ll;
    else
    {
        if (v1==v) 
        {
            if (v2==INF) return 123456789876543ll;
            else return sum+v-v2;
        }
        else return sum+v-v1;
    }
}
 
int main()
{
    readint(n);
    readint(m);
    for (int a=1;a<=m;a++)
        e[a].init();
    sort(e+1,e+m+1);
    for (int a=1;a<=n;a++)
        ff[a]=a;
    int cnt=0;
    for (int a=1;a<=m;a++)
    {
        int f1=getf(e[a].s);
        int f2=getf(e[a].e);
        if (f1!=f2)
        {
            ff[f1]=f2;
            e[a].mst=true;
            add_edge(e[a].s,e[a].e,e[a].d);
            add_edge(e[a].e,e[a].s,e[a].d);
            cnt++;
            sum+=e[a].d;
            if (cnt==n-1) break;
        }
    }
    ans=123456789876543ll;
    bfs();
    for (int a=1;a<=m;a++)
        if (!e[a].mst) ans=min(ans,getans(e[a].s,e[a].e,e[a].d));
    if (ans==123456789876543ll) printf("-1\n");
	else cout << ans << endl;
 
    return 0;
}

