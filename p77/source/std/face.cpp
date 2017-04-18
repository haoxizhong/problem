#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long dint;
#define _l (long long int)

const int maxn = 220003;
const int inf = 0x3f3f3f3f;

inline dint sqr(const dint& x) {
	return x * x;
}

inline dint dist(int a, int b, int c, int d) {
	return sqr(c - a) + sqr(b - d);
}

struct KNode {
	int r[2][2], p[2], v, s, i;
	KNode *ch[2], *pt;
};

#define upMin(_a_,_b_) { \
	if (_a_ > _b_) { \
		_a_ = _b_; \
	} \
}
#define upMax(_a_,_b_) { \
	if (_a_ < _b_) { \
		_a_ = _b_; \
	} \
}

struct Event {
	int c, i, t;
};

inline bool operator <(const Event& a, const Event& b) {
	return a.c < b.c || (a.c == b.c && a.t < b.t);
}

KNode kpool[maxn], *npt[maxn], *krt;
int n, m, ans[maxn], cans, cqx, cqy, kw;
dint clen;
int px[maxn], py[maxn], pc[maxn], qx[maxn], qy[maxn], qc[maxn];
Event e[maxn];

void update(KNode* p) {
	if (p->ch[0]) {
		upMin(p->r[0][0], p->ch[0]->r[0][0]);
		upMax(p->r[0][1], p->ch[0]->r[0][1]);
		upMin(p->r[1][0], p->ch[0]->r[1][0]);
		upMax(p->r[1][1], p->ch[0]->r[1][1]);
		upMin(p->s, p->ch[0]->s);
	}
	if (p->ch[1]) {
		upMin(p->r[0][0], p->ch[1]->r[0][0]);
		upMax(p->r[0][1], p->ch[1]->r[0][1]);
		upMin(p->r[1][0], p->ch[1]->r[1][0]);
		upMax(p->r[1][1], p->ch[1]->r[1][1]);
		upMin(p->s, p->ch[1]->s);
	}
}

inline bool cmpKd(const KNode& a, const KNode& b) {
	return (a.p[kw] < b.p[kw]) || (a.p[kw] == b.p[kw] && a.p[kw ^ 1] < b.p[kw ^ 1]);
}

KNode* kdBuild(KNode* l, KNode* r) {
	if (l == r) {
		return 0;
	}
	if (l + 1 == r) {
		l->ch[0] = l->ch[1] = 0;
		return l;
	}
	kw ^= 1;
	KNode* md(l + ((r - l) >> 1));
	nth_element(l, md, r, cmpKd);
	KNode* ret(md);
	ret->ch[0] = kdBuild(l, md);
	if (ret->ch[0]) {
		ret->ch[0]->pt = ret;
	}
	ret->ch[1] = kdBuild(md + 1, r);
	if (ret->ch[1]) {
		ret->ch[1]->pt = ret;
	}
	ret->pt = 0;
	return ret;
}

void updateAns(int i) {
	dint d(dist(px[i], py[i], cqx, cqy));
	if (d < clen || (d == clen && i < cans)) {
		cans = i;
		clen = d;
	}
}
dint estiDis(KNode* p) {
	if (!p) {
		return 0x3f3f3f3f3f3f3f3fll;
	}
	return sqr(max(p->r[0][0] - cqx, 0) + max(cqx - p->r[0][1], 0)) + sqr(max(p->r[1][0] - cqy, 0)+ max(cqy - p->r[1][1], 0));
}

void kdQry(KNode* p) {
	if (!p || p->s == inf) {
		return;
	}
	if (p->v < inf) {
		updateAns(p->i);
	}
	dint e[2];
	int x(0);
	e[0] = estiDis(p->ch[0]), e[1] = estiDis(p->ch[1]);
	if (e[0] > e[1]) {
		x ^= 1;
	}
	if (e[x] <= clen) {
		kdQry(p->ch[x]);
	}
	if (e[x ^ 1] <= clen) {
		kdQry(p->ch[x ^ 1]);
	}
}

void sovK() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d%d", px + i, py + i, pc + i);
		e[i].c = pc[i];
		e[i].i = i;
		e[i].t = 0;
		kpool[i].r[0][0] = kpool[i].r[1][0] = inf;
		kpool[i].r[0][1] = kpool[i].r[1][1] = -inf;
		kpool[i].p[0] = px[i], kpool[i].p[1] = py[i];
		kpool[i].s = kpool[i].v = inf;
		kpool[i].i = i;
	}
	kw = 0;
	krt = kdBuild(kpool, kpool + n);
	for (int i = 0; i < n; ++ i) {
		npt[kpool[i].i] = kpool + i;
	}
	for (int i = 0; i < m; ++ i) {
		scanf("%d%d%d", qx + i, qy + i, qc + i);
		e[i + n].c = qc[i];
		e[i + n].i = i;
		e[i + n].t = 1;
	}
	sort(e, e + m + n);
	for (int i = 0; i < m + n; ++ i) {
		if (e[i].t == 0) {
			upMin(npt[e[i].i]->r[0][0], px[e[i].i]);
			upMax(npt[e[i].i]->r[0][1], px[e[i].i]);
			upMin(npt[e[i].i]->r[1][0], py[e[i].i]);
			upMax(npt[e[i].i]->r[1][1], py[e[i].i]);
			upMin(npt[e[i].i]->s, e[i].i);
			npt[e[i].i]->v = e[i].i;
			for (KNode* p = npt[e[i].i]->pt; p; p = p->pt) {
				update(p);
			}
		} else {
			cans = -1;
			clen = 0x3f3f3f3f3f3f3f3fll;
			cqx = qx[e[i].i], cqy = qy[e[i].i];
			kdQry(krt);
			ans[e[i].i] = cans;
		}
	}
	for (int i = 0; i < m; ++ i) {
		printf("%d %d %d\n", px[ans[i]], py[ans[i]], pc[ans[i]]);
	}
}

int main() {
	int t=1;
	while (t --) {
		sovK();
	}
}
