#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

using namespace std;

#define inc(a,b) {a+=b;if (a>=mo) a-=mo;}
#define newnode ++wmt

const int maxn=210;
const int maxm=22;
const int maxk=510;
const int maxp=210;
const int mo=1000000007;

int n,m,k,llen,rlen,wmt,root,f[maxn][maxp][maxk][2],l[maxn],r[maxn],s[maxn],q[maxp];

struct node
{
	int next[maxm];
	int value,fail;
	node()
	{
		memset(next,0,sizeof(next));
		value=fail=0;
	}
}z[maxp];

void insert(int *s,int l,int v)
{
	int p=root;
	for (int a=1;a<=l;a++)
	{
		if (!z[p].next[s[a]]) z[p].next[s[a]]=newnode;
		p=z[p].next[s[a]];
	}
	z[p].value+=v;
}

void build_AC()
{
	int front=1,tail=1;
	q[1]=root;
	for (;front<=tail;)
	{
		int now=q[front++];
		for (int a=0;a<m;a++)
			if (z[now].next[a])
			{
				int p=z[now].fail;
				while (p)
				{
					if (z[p].next[a])
					{
						z[z[now].next[a]].fail=z[p].next[a];
						break;
					}
					p=z[p].fail;
				}
				if (!p) z[z[now].next[a]].fail=root;
				z[z[now].next[a]].value+=z[z[z[now].next[a]].fail].value;
				q[++tail]=z[now].next[a];
			}
			else
			{
				z[now].next[a]=z[z[now].fail].next[a];
				if (!z[now].next[a]) z[now].next[a]=root;
			}
	}
}

int solve(int *y,int l)
{
	if (!l) return 0;
	int ans=0;
	for (int a=1;a<l;a++)
		for (int b=1;b<=wmt;b++)
			for (int c=0;c<=k;c++)
				inc(ans,f[a][b][c][0]);
	for (int a=l;a>=1;a--)
		for (int b=1;b<=wmt;b++)
			for (int c=(a==l);c+(a!=1)<=y[a];c++)
			{
				int p=b,delta=0;
				p=z[p].next[c];
				delta+=z[p].value;
				for (int d=a+1;d<=l;d++)
				{
					p=z[p].next[y[d]];
					delta+=z[p].value;
				}
				for (int d=0;d<=k-delta;d++)
					for (int e=0;e<=1;e++)
						inc(ans,f[a-1][b][d][e]);
			}
	return ans;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	scanf("%d",&llen);
	for (int a=llen;a>=1;a--)
		scanf("%d",&l[a]);
	scanf("%d",&rlen);
	for (int a=rlen;a>=1;a--)
		scanf("%d",&r[a]);
	root=newnode;
	for (int a=1,v;a<=n;a++)
	{
		int l;
		scanf("%d",&l);
		for (int b=1;b<=l;b++)
			scanf("%d",&s[b]);
		reverse(s+1,s+l+1);
		scanf("%d",&v);
		insert(s,l,v);
	}
	build_AC();
	n=max(llen,rlen);
	f[0][root][0][0]=1;
	for (int a=0;a<n;a++)
		for (int b=1;b<=wmt;b++)
			for (int c=0;c<=k;c++)
				for (int d=0;d<=1;d++)
					if (f[a][b][c][d])
						for (int e=0;e<m;e++)
							if (c+z[z[b].next[e]].value<=k) inc(f[a+1][z[b].next[e]][c+z[z[b].next[e]].value][e==0],f[a][b][c][d]);
	l[1]--;
	for (int a=1;a<=llen;a++)
		if (l[a]<0) l[a]+=m,l[a+1]--;
		else break;
	if (!l[llen]) llen--;
	printf("%d\n",(solve(r,rlen)-solve(l,llen)+mo)%mo);

	return 0;
}
