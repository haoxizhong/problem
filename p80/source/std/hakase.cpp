#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<algorithm>
#include<map>

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

int n,y,k,x,en,z[maxn],mul[maxn],divi[maxn];

int cnt,f[maxn],belong[maxn],q[maxn],size[maxn],weight[maxn];

bool vis[maxn];

int value[maxn][2],len[maxn],root[maxn];

int now_to_other[maxn][2],other_to_now[maxn][2];

int now_to_other_map[maxn],other_to_now_map[maxn],now_to_other_son_map[maxn],other_to_now_son_map[maxn];

int size1,size2;

struct edge
{
	int e;
	edge *next;
}*v[maxn],ed[maxn<<1];

inline void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
}

void init()
{
	readint(n);
	readint(y);
	readint(k);
	readint(x);
	for (int a=1;a<=n;a++)
	{
		readint(z[a]);
	}
	int s,e;
	for (int a=1;a<n;a++)
	{
		readint(s);
		readint(e);
		add_edge(s,e);
		add_edge(e,s);
	}
}

inline int pow(int a,int b)
{
	int ans=1;
	while (b)
	{
		if (b&1) ans=(long long)ans*a%y;
		a=(long long)a*a%y;
		b>>=1;
	}
	return ans;
}

int get_mid(int now)
{
    cnt++;
    f[now]=0;
    belong[now]=cnt;
    int front=1,tail=1;
    q[front]=now;
	for (;front<=tail;)
    {
        int now=q[front++];
        size[now]=weight[now]=0;
        for (edge *e=v[now];e;e=e->next)
            if (!vis[e->e] && belong[e->e]!=cnt)
            {
                f[e->e]=now;
                belong[e->e]=cnt;
                q[++tail]=e->e;
            }
    }
    for (int a=tail;a>=1;a--)
    {
        int now=q[a];
        size[now]++;
        size[f[now]]+=size[now];
        weight[f[now]]=max(weight[f[now]],size[now]);
        weight[now]=max(weight[now],tail-size[now]);
    }
    int p=q[1];
    for (int a=2;a<=tail;a++)
        if (weight[q[a]]<weight[p]) p=q[a];
    return p;
}

inline int calc1(int a)
{
	return (long long)(x-value[a][0]+y)*divi[len[a]]%y;
}

inline int calc2(int a)
{
	int v2=(value[a][0]-(long long)z[root[a]]*mul[len[a]-1]%y+y)%y;
	return (long long)(x-v2+y)*divi[len[a]-1]%y;
}

void work(int px,int p)
{
	cnt++;
	int front=1,tail=1;
	q[1]=px;
	len[px]=2;
	value[px][0]=((long long)z[p]*k+z[px])%y;
	value[px][1]=((long long)z[px]*k+z[p])%y;
	for (;front<=tail;)
	{
		int now=q[front++];
		belong[now]=cnt;
		root[now]=p;
		now_to_other_map[++size1]=value[now][1];
		int rex=calc1(now);
		other_to_now_map[size1]=rex;
		for (edge *e=v[now];e;e=e->next)
			if (belong[e->e]!=cnt && !vis[e->e])
			{
				q[++tail]=e->e;
				value[e->e][0]=((long long)value[now][0]*k+z[e->e])%y;
				value[e->e][1]=((long long)z[e->e]*mul[len[now]]+value[now][1])%y;
				len[e->e]=len[now]+1;
			}
	}
}

inline int calc(int *z,int n,int v)
{
	int l=0,r=n;
	while (l+1!=r)
	{
		int m=(l+r)>>1;
		if (z[m]>=v) r=m;
		else l=m;
	}
	if (z[r]!=v) return 0;
	int pl=r;
	l=1,r=n+1;
	while (l+1!=r)
	{
		int m=(l+r)>>1;
		if (z[m]<=v) l=m;
		else r=m;
	}
	return (l-pl+1);
}

void solve(int px,int p)
{
	cnt++;
	int front=1,tail=1;
	q[1]=px;
	size2=0;
	for (;front<=tail;)
	{
		int now=q[front++];
		belong[now]=cnt;
		now_to_other_son_map[++size2]=value[now][1];
		int rex=calc1(now);
		other_to_now_son_map[size2]=rex;
		for (edge *e=v[now];e;e=e->next)
			if (root[e->e]==p && belong[e->e]!=cnt) q[++tail]=e->e;
	}
	sort(now_to_other_son_map+1,now_to_other_son_map+size2+1);
	sort(other_to_now_son_map+1,other_to_now_son_map+size2+1);
	for (int a=1;a<=tail;a++)
	{
		int now=q[a];
		int need=(long long)(value[now][1]-z[p]+y)*divi[1]%y;
		other_to_now[now][1]+=calc(other_to_now_map,size1,need)-calc(other_to_now_son_map,size2,need);
		need=calc2(now);
		now_to_other[now][1]+=calc(now_to_other_map,size1,need)-calc(now_to_other_son_map,size2,need);
	}
}

void dfs(int now)
{
	int p=get_mid(now);
	vis[p]=true;
	size1=0;
	now_to_other_map[++size1]=z[p];
	other_to_now_map[size1]=(long long)(x-z[p]+y)*divi[1]%y;
	for (edge *e=v[p];e;e=e->next)
		if (!vis[e->e]) work(e->e,p);
	sort(now_to_other_map+1,now_to_other_map+size1+1);
	sort(other_to_now_map+1,other_to_now_map+size1+1);
	for (edge *e=v[p];e;e=e->next)
		if (!vis[e->e]) solve(e->e,p);
	now_to_other[p][1]+=calc(now_to_other_map,size1,x);
	other_to_now[p][1]+=calc(other_to_now_map,size1,0);
	for (edge *e=v[p];e;e=e->next)
		if (!vis[e->e]) dfs(e->e);
}

void prework()
{
	mul[0]=1;
	for (int a=1;a<=n;a++)
		mul[a]=(long long)mul[a-1]*k%y;
	divi[0]=1;
	divi[1]=pow(mul[1],y-2);
	for (int a=2;a<=n;a++)
		divi[a]=(long long)divi[a-1]*divi[1]%y;
	dfs(1);
}

void solve()
{
	long long tot=0;
	for (int a=1;a<=n;a++)
	{
		now_to_other[a][0]=n-now_to_other[a][1];
		other_to_now[a][0]=n-other_to_now[a][1];
		int num1=now_to_other[a][0];
		int num2=now_to_other[a][1];
		int num3=other_to_now[a][0];
		int num4=other_to_now[a][1];
		tot+=(long long)num1*num2*2+(long long)num1*num4+(long long)num2*num3+(long long)num3*num4*2;
	}
	printf("%I64d\n",(long long)n*n*n-tot/2);
}

int main()
{
	freopen("hakase.in","r",stdin);
	freopen("hakase.out","w",stdout);

	init();
	prework();
	solve();

	return 0;
}

