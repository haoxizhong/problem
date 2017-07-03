#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<algorithm>

using namespace std;

#define elif else if

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

#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

const int maxn=100010;
const int maxp=maxn<<2|1;
const int maxv=10010;

int n,m,p;

int lcm,match[maxv],use[maxv],length_in_circle[maxv],length_out_of_circle[maxv];

int z[maxn],rest[maxp],bitv[maxp][100],lift[maxp],rest_sum[maxp],nowp[maxp];

int gcd(int a,int b)
{
	if (!b) return a;
	else return gcd(b,a%b);
}

void update(int rt)
{
	for (int a=0;a<lcm;a++)
		bitv[rt][a]=bitv[rt<<1][(a+lift[rt<<1]+nowp[rt<<1])%lcm]+bitv[rt<<1|1][(a+lift[rt<<1|1]+nowp[rt<<1|1])%lcm];
	rest_sum[rt]=rest_sum[rt<<1]+rest_sum[rt<<1|1];
	rest[rt]=rest[rt<<1]+rest[rt<<1|1];
	nowp[rt]=0;
}

void push_col(int rt)
{
	if (lift[rt])
	{
		lift[rt<<1]+=lift[rt];
		lift[rt<<1|1]+=lift[rt];
		nowp[rt]+=lift[rt];
		lift[rt]=0;
	}
}

void build(int l,int r,int rt)
{
	if (l==r)
	{
		readint(z[l]);
		if (length_out_of_circle[z[l]]) rest[rt]=1,rest_sum[rt]=z[l];
		else
		{
			for (int a=0,b=z[l];a<lcm;a++,b=b*b%p)
				bitv[rt][a]+=b;
			rest[rt]=rest_sum[rt]=0;
		}
		return;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	update(rt);
}

void modify(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l && r<=nowr)
	{
		if (rest[rt])
		{
			if (l==r)
			{
				z[l]=z[l]*z[l]%p;
				if (length_out_of_circle[z[l]]) rest[rt]=1,rest_sum[rt]=z[l];
				else
				{
					for (int a=0,b=z[l];a<lcm;a++,b=b*b%p)
						bitv[rt][a]+=b;
					rest[rt]=rest_sum[rt]=0;
				}
			}
			else
			{
				int m=(l+r)>>1;
				modify(lson,nowl,nowr);
				modify(rson,nowl,nowr);
				update(rt);
			}
		}
		else lift[rt]++;
		return;
	}
	push_col(rt);
	int m=(l+r)>>1;
	if (nowl<=m) modify(lson,nowl,nowr);
	if (m<nowr) modify(rson,nowl,nowr);
	update(rt);
}

int query(int l,int r,int rt,int nowl,int nowr)
{
	if (nowl<=l && r<=nowr) return bitv[rt][(lift[rt]+nowp[rt])%lcm]+rest_sum[rt];
	push_col(rt);
	int m=(l+r)>>1;
	if (nowl<=m)
	{
		if (m<nowr) return query(lson,nowl,nowr)+query(rson,nowl,nowr);
		else return query(lson,nowl,nowr);
	}
	else return query(rson,nowl,nowr);
}

void find(int p)
{
	for (int a=0;a<p;a++)
	{
		use[a]=a;
		match[a]=1;
		length_out_of_circle[a]=1;
		for (int v=a;;length_out_of_circle[a]++)
		{
			v=v*v%p;
			if (use[v]==a)
			{
				length_in_circle[a]=length_out_of_circle[a]-match[v]+1;
				length_out_of_circle[a]=match[v]-1;
				break;
			}
			match[v]=length_out_of_circle[a]+1;
			use[v]=a;
		}
	}	
	lcm=1;
	for (int a=0;a<p;a++)
		lcm=lcm/gcd(lcm,length_in_circle[a])*length_in_circle[a];
}

int main()
{
	readint(n);
	readint(m);
	readint(p);
	find(p);
	build(1,n,1);
	for (int a=1;a<=m;a++)
	{
		int opt,l,r;
		readint(opt);
		readint(l);
		readint(r);
		if (l>r) return 0;
		if (!opt) modify(1,n,1,l,r);
		else printf("%d\n",query(1,n,1,l,r));
	}

	return 0;
}
