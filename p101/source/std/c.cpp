#include <cstdio>
#include <cctype>
#include <memory.h>
#include <algorithm>

using namespace std;

typedef long long qw;

#ifdef WIN32
#define lld "%I64d"
#else
#define lld "%lld"
#endif

int nextInt() {
	int s = 0, d;
	bool nag = 0;
	do {
		d = getchar();
		if (d == '-')
			nag = 1;
	} while (!isdigit(d));
	do
		s = s * 10 + d - 48, d = getchar();
	while (isdigit(d));
	return nag ? -s : s;
}

struct seg {
	int l, r;
	qw v, z;
	seg *ls, *rs;
};
struct obj {
	int l, r, v;
};

inline bool cmpObj(const obj& a, const obj& b) {
	return (a. l < b. l) || (a. l == b. l && a. r < b. r);
}

const int maxn = 200009;
const qw inf = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
obj q[maxn];
qw s[maxn], ans;
seg *rtf, *rtc, *sp;

#define mid(p) ((p->l+p->r)>>1)

seg *sgtBuild(int l, int r) {
	seg *p = sp ++;
	p-> v = - inf;
	p-> z = 0;
	p-> l = l;
	p-> r = r;
	if (l + 1 < r) {
		p-> ls = sgtBuild(l, mid(p));
		p-> rs = sgtBuild(mid(p), r);
	}
	return p;
}

void sgtChg(seg* p, int p0, qw v0) {
	if (p-> l + 1 == p-> r)
		p-> v = max(p-> v, v0);
	else {
		if (p0 < mid(p))
			sgtChg(p-> ls, p0, v0 - p-> z);
		else
			sgtChg(p-> rs, p0, v0 - p-> z);
		p-> v = max(p-> ls-> v, p-> rs-> v) + p-> z;
	}
}

qw sgtQry(seg* p, int l, int r) {
	if (l >= r)
		return -inf;
	else if (p-> l == l && p-> r == r)
		return p-> v;
	else if (r <= mid(p))
		return sgtQry(p-> ls, l, r) + p-> z;
	else if (l >= mid(p))
		return sgtQry(p-> rs, l, r) + p-> z;
	else
		return max(sgtQry(p-> ls, l, mid(p)), sgtQry(p-> rs, mid(p), r)) + p-> z;
}

void sgtLazy(seg* p, int l, qw z0) {
	if (p-> v == -inf)
		return;
	else if (p-> l == l)
		p-> v += z0, p-> z += z0;
	else {
		if (l < mid(p)) {
			sgtLazy(p-> ls, l, z0);
			sgtLazy(p-> rs, mid(p), z0);
		}
		else
			sgtLazy(p-> rs, l, z0);
		p-> v = max(p-> ls-> v, p-> rs-> v) + p-> z;
	}
}

int main() {
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	sp = new seg[maxn * 6];
	n = nextInt();
	m = nextInt();
	rtf = sgtBuild(0, n + 2);
	rtc = sgtBuild(0, n + 2);
	s[0] = 0;
	for (int i = 1; i <= n; i ++)
		s[i] = s[i - 1] + nextInt();
	for (int i = 0; i < m; i ++) {
		q[i]. l = nextInt();
		q[i]. r = nextInt();
		q[i]. v = nextInt();
	}
	sort(q, q + m, cmpObj);
	ans = 0;
	for (int i = 0; i < m; i ++) {
		qw res0 = max(sgtQry(rtf, 0, q[i]. l), 0LL) - s[q[i]. r] + s[q[i]. l - 1];
		qw res1 = sgtQry(rtc, q[i]. l, q[i]. r + 1) - s[q[i]. r];
		qw res = max(max(res0, res1), sgtQry(rtf, q[i]. r, n + 1)) + q[i]. v;
		sgtLazy(rtf, q[i]. r, q[i]. v);
		sgtLazy(rtc, q[i]. r, q[i]. v);
		sgtChg(rtf, q[i]. r, res);
		sgtChg(rtc, q[i]. r, res + s[q[i]. r]);
		ans = max(ans, res);
	}
	printf(lld "\n", ans);
}
