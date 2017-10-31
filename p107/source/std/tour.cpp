#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<algorithm>
 
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
 
#define wmt 1,cnt,1
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
 
const int maxn=200010;
 
int n,k,en,z[maxn],f[maxn],s[maxn],leaf[maxn],l[maxn],r[maxn];
 
long long y[maxn<<2|1],col[maxn<<2|1];
 
bool del[maxn];
 
struct edge
{
    int e;
    edge *next;
}*v[maxn],*ve[maxn],ed[maxn];
 
inline void add_edge(int s,int e)
{
    en++;
    ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}
 
#define update(rt) y[rt]=max(y[rt<<1],y[rt<<1|1]);
 
#define push_col(rt)\
    if (col[rt])\
    {\
        col[rt<<1]+=col[rt];y[rt<<1]+=col[rt];\
        col[rt<<1|1]+=col[rt];y[rt<<1|1]+=col[rt];\
        col[rt]=0;\
    }
 
inline void modify(int l,int r,int rt,int nowl,int nowr,int delta)
{
    if (nowl<=l && r<=nowr)
    {
        y[rt]+=delta;
        col[rt]+=delta;
        return;
    }
    push_col(rt);
    int m=(l+r)>>1;
    if (nowl<=m) modify(lson,nowl,nowr,delta);
    if (m<nowr) modify(rson,nowl,nowr,delta);
    update(rt);
}
 
inline int query(int l,int r,int rt)
{
    if (l==r) return l;
    push_col(rt);
    int m=(l+r)>>1;
    if (y[rt<<1]>y[rt<<1|1]) return query(lson);
    else return query(rson);
}
 
int main()
{
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);

    readint(n);
    readint(k);
    for (int a=1;a<=n;a++)
    {
        readint(z[a]);
    }
    for (int a=1;a<n;a++)
    {
        int p1,p2;
        readint(p1);
        readint(p2);
        f[p2]=p1;
        add_edge(p1,p2);
    }
    int root;
    for (int a=1;a<=n;a++)
        if (!f[a]) root=a;
    int size=1;
    s[1]=root;
    for (int a=1;a<=n;a++)
        ve[a]=v[a];
    memset(l,0x3f,sizeof(l));
    int cnt=0;
    while (size)
    {
        int now=s[size];
        if (!ve[now])
        {
            if (!v[now]) 
            {
                l[now]=r[now]=++cnt;
                leaf[cnt]=now;
            }
            l[f[now]]=min(l[f[now]],l[now]);
            r[f[now]]=max(r[f[now]],r[now]);
            size--;
        }
        else
        {
            size++;
            s[size]=ve[now]->e;
            ve[now]=ve[now]->next;
        }
    }
    for (int a=1;a<=n;a++)
        modify(wmt,l[a],r[a],z[a]);
    k=min(k,cnt);
    long long ans=0;
    for (int a=1;a<=k;a++)
    {
        int p=query(wmt);
        p=leaf[p];
        while (!del[p] && p)
        {
            modify(wmt,l[p],r[p],-z[p]);
            ans+=z[p];
            del[p]=true;
            p=f[p];
        }
    }
    printf("%I64d\n",ans);
 
    return 0;
}
