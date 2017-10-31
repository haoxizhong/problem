#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

#ifdef unix
#define LLX "%lld"
#else
#define LLX "%I64d"
#endif

typedef unsigned int USN;
typedef long long LL;
typedef unsigned long long ULL;

#define rep(i,l,r) for (int i=(l); i<=(r); i++)
#define repd(i,r,l) for (int i=(r); i>=(l); i--)

#define maxn 100100
#define MD 1000000007

inline int getbit(int k, int b)
{
	return (k & (1<<b))>0;
}

int final=0;
int dat[maxn];
struct node
{
	int cnt;
	vector<int> a[maxn];
	node() { cnt=0; }
	void clear()
	{
		rep(i,1,cnt) a[i].clear();
		cnt=0;
	}
};
node t[2];
LL kth;

int ac0[32],ac1[32],bc0[32],bc1[32];

void addup(int bitlim, vector<int> &a, vector<int> &b)
{
	memset(ac0,0,sizeof ac0);
	memset(ac1,0,sizeof ac1);
	for (vector<int>::iterator iter=a.begin(); iter!=a.end(); iter++)
	{
		int x=*iter;
		rep(i,0,bitlim) if (x&(1<<i)) ac1[i]++; else ac0[i]++;
	}
	memset(bc0,0,sizeof bc0);
	memset(bc1,0,sizeof bc1);
	for (vector<int>::iterator iter=b.begin(); iter!=b.end(); iter++)
	{
		int x=*iter;
		rep(i,0,bitlim) if (x&(1<<i)) bc1[i]++; else bc0[i]++;
	}
	rep(i,0,bitlim) final=((LL((LL(ac0[i])*bc1[i]+LL(ac1[i])*bc0[i])%MD)<<i)+final)%MD;
}

int _c0[maxn], _c1[maxn], _ac0[maxn], _ac1[maxn], _bc0[maxn], _bc1[maxn];

void solve2(int bit, int cur, int next)
{
	if (bit<0) return;
	t[next].clear(); LL s=0;
	for (int i=1; i<=t[cur].cnt; i+=2)
	{
		int ac0=0, ac1=0;
		for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
			if (getbit(*iter,bit)) ac1++; else ac0++;

		int bc0=0, bc1=0;
		for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
			if (getbit(*iter,bit)) bc1++; else bc0++;

		s+=LL(ac0)*bc1+LL(ac1)*bc0;
		_ac0[i]=ac0; _ac1[i]=ac1; _bc0[i]=bc0; _bc1[i]=bc1;
	}
	if (s<=kth)
	{
		kth-=s;
		for (int i=1; i<=t[cur].cnt; i+=2)
		{
			int ac0=_ac0[i], ac1=_ac1[i], bc0=_bc0[i], bc1=_bc1[i];
			for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
				if (getbit(*iter,bit)) 
					t[next].a[t[next].cnt+3].push_back(*iter); 
				else  t[next].a[t[next].cnt+1].push_back(*iter);
			
			for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
				if (getbit(*iter,bit))
					t[next].a[t[next].cnt+4].push_back(*iter); 
				else  t[next].a[t[next].cnt+2].push_back(*iter);
			
			if (ac0 && bc1) addup(bit,t[next].a[t[next].cnt+1],t[next].a[t[next].cnt+4]);
			if (ac1 && bc0) addup(bit,t[next].a[t[next].cnt+2],t[next].a[t[next].cnt+3]);
			
			rep(k,1,4) t[next].a[t[next].cnt+k].clear();
			if (ac0 && bc0)
			{
				for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
					if (!getbit(*iter,bit)) 
						t[next].a[t[next].cnt+1].push_back(*iter);
				
				for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
					if (!getbit(*iter,bit))
						t[next].a[t[next].cnt+2].push_back(*iter);
				
				t[next].cnt+=2;
			}
			if (ac1 && bc1)
			{
				for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
					if (getbit(*iter,bit)) 
						t[next].a[t[next].cnt+1].push_back(*iter); 
				
				for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
					if (getbit(*iter,bit))
						t[next].a[t[next].cnt+2].push_back(*iter); 
				
				t[next].cnt+=2;
			}
		}
		solve2(bit-1,next,cur);
	}
	else
	{
		final=((LL(kth%MD)<<bit)+final)%MD;
		for (int i=1; i<=t[cur].cnt; i+=2)
		{
			int ac0=_ac0[i], ac1=_ac1[i], bc0=_bc0[i], bc1=_bc1[i];
			if (ac0 && bc1)
			{
				for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
					if (!getbit(*iter,bit)) 
						t[next].a[t[next].cnt+1].push_back(*iter); 
				
				for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
					if (getbit(*iter,bit))
						t[next].a[t[next].cnt+2].push_back(*iter); 
			
				t[next].cnt+=2;
			}
			if (ac1 && bc0)
			{
				for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
					if (getbit(*iter,bit)) 
						t[next].a[t[next].cnt+1].push_back(*iter); 
			
				for (vector<int>::iterator iter=t[cur].a[i+1].begin(); iter!=t[cur].a[i+1].end(); iter++)
					if (!getbit(*iter,bit))
						t[next].a[t[next].cnt+2].push_back(*iter); 
			
				t[next].cnt+=2;
			}
		}
		solve2(bit-1,next,cur);
	}
}	
			
void solve1(int bit, int cur, int next)
{
	if (bit<0) return;
	t[next].clear(); LL s=0; 
	rep(i,1,t[cur].cnt)
	{
		int c0=0, c1=0;
		for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
			if (getbit(*iter,bit)) c1++; else c0++;
		s+=LL(c0)*c1;
		_c0[i]=c0; _c1[i]=c1;
	}
	if (s<=kth)
	{
		kth-=s;
		rep(i,1,t[cur].cnt)
		{
			int w0,w1,c0=_c0[i],c1=_c1[i];
			if (c0) w0=1, w1=2; else w1=1;
			for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
				if (getbit(*iter,bit))
					t[next].a[t[next].cnt+w1].push_back(*iter);
				else  t[next].a[t[next].cnt+w0].push_back(*iter);
				
			if (c0 && c1) addup(bit,t[next].a[t[next].cnt+1], t[next].a[t[next].cnt+2]);
			if (c0) t[next].cnt++;
			if (c1) t[next].cnt++;
		}
		solve1(bit-1,next,cur);
	}
	else
	{
		final=((LL(kth%MD)<<bit)+final)%MD;
		rep(i,1,t[cur].cnt)
		{
			int c0=_c0[i], c1=_c1[i];
			if (c0 && c1)
			{
				for (vector<int>::iterator iter=t[cur].a[i].begin(); iter!=t[cur].a[i].end(); iter++)
					if (getbit(*iter,bit))
						t[next].a[t[next].cnt+2].push_back(*iter);
					else  t[next].a[t[next].cnt+1].push_back(*iter);
				t[next].cnt+=2;
			}
		}
		solve2(bit-1,next,cur);
	}
}
		
void lemon()
{
	int n; scanf("%d" LLX,&n,&kth);
	rep(i,1,n) scanf("%d",&dat[i]);
	
	int cur=0, next=1;
	t[cur].clear(); t[cur].cnt++; 
	rep(i,1,n) t[cur].a[t[cur].cnt].push_back(dat[i]);
	solve1(30,cur,next);
	
	printf("%d\n",final);
}

int main()
{
	freopen("war.in","r",stdin);
	freopen("war.out","w",stdout);

	ios::sync_with_stdio(true);
	lemon();
	return 0;
}
