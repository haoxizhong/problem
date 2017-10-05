#define PROC "b"
#include <cstdio>
#include <memory.h>
#include <algorithm>

using namespace std;

typedef long long qw;

#ifdef WIN32
#define lld "%I64d"
#else
#define lld "%lld"
#endif
#define _l (qw)

struct edge {
	int t, c;
	edge *next;
};

const int maxn = 300009;

int n, v[maxn], tm[maxn], d[maxn], cf[maxn], fa[maxn], *r[maxn];
int ea[maxn], eb[maxn], ec[maxn];
qw sc[maxn], sz[maxn], csc[maxn], csz[maxn], ans;
edge *ep, *head[maxn];

inline bool cmpP(int* a, int* b) {
	return *a < *b;
}

inline void addEdge(int u, int v, int c) {
	ep-> t = v;
	ep-> c = c;
	ep-> next = head[u];
	head[u] = ep ++;
}

qw getVal(qw* a, int t, int p) {
	if (tm[p] ^ t) {
		tm[p] = t;
		csc[p] = 0;
		csz[p] = 0;
		return 0;
	}
	else
		return a[p];
}

qw sov() {
	static int q[maxn];
	int hd = 0, tl = 1;
	qw ans = 0;
	memset(d, 0, sizeof(d));
	d[1] = 1;
	q[hd] = 1;
	cf[1] = 0;
	fa[1] = 0;
	while (hd < tl) {
		int p = q[hd ++];
		for (edge* e = head[p]; e; e = e-> next)
			if (!d[e-> t]) {
				d[e-> t] = d[p] + 1;
				cf[e-> t] = e-> c;
				fa[e-> t] = p;
				q[tl ++] = e-> t;
			}
	}
	for (int ti = tl - 1; ti >= 0; ti --) {
		int p = q[ti];
		qw tsc = 0, tsz = 0;
		sz[p] = 1;
		sc[p] = 0;
		for (edge* e = head[p]; e; e = e-> next)
			if (d[e-> t] == d[p] + 1) {
				qw qsc = tsc - getVal(csc, p, e-> c); 
				qw qsz = tsz - getVal(csz, p, e-> c);
				ans += qsc * sz[e-> t] + qsz * sc[e-> t] + qsz * sz[e-> t] * v[p];
				ans += sc[e-> t] + sz[e-> t] * v[p];
				if (e-> c ^ cf[p]) {
					sz[p] += sz[e-> t];
					sc[p] += sc[e-> t];
				}
				csc[e-> c] += sc[e-> t];
				csz[e-> c] += sz[e-> t];
				tsc += sc[e-> t];
				tsz += sz[e-> t];
			}
		sc[p] += sz[p] * v[p];
	}
	return ans;
}

int main() {
	
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
	memset(tm, 0, sizeof(tm));
	memset(head, 0, sizeof(head));
	ep = new edge[maxn * 2];
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", v + i);
	for (int i = 0; i < n - 1; i ++)
		scanf("%d%d%d", ea + i, eb + i, ec + i), r[i] = ec + i;
	sort(r, r + n - 1, cmpP);
	for (int i = 0, l = -1, v = 0; i < n - 1; i ++)
		if (*r[i] == l)
			*r[i] = v;
		else
			l = *r[i], *r[i] = ++ v;
	for (int i = 0; i < n - 1; i ++) {
		addEdge(ea[i], eb[i], ec[i]);
		addEdge(eb[i], ea[i], ec[i]);
	}
	ans = sov();
	printf(lld "\n", ans);
}
