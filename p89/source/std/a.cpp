//Template
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <climits>
#include <cmath>
#include <utility>
#include <set>
#include <map>
#include <queue>
#include <ios>
#include <iomanip>
#include <ctime>
#include <numeric>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cstdarg>
#include <complex>
using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long double ld;
#define pair(x, y) make_pair(x, y)
#define runtime() ((double)clock() / CLOCKS_PER_SEC)

inline int read() {
	static int r, sign;
	static char c;
	r = 0, sign = 1;
	do c = getchar(); while (c != '-' && (c < '0' || c > '9'));
	if (c == '-') sign = -1, c = getchar();
	while (c >= '0' && c <= '9') r = r * 10 + (int)(c - '0'), c = getchar();
	return sign * r;
}

template <typename T>
inline void print(T *a, int n) {
	for (int i = 1; i < n; ++i) cout << a[i] << " ";
	cout << a[n] << endl;
}
#define PRINT(_l, _r, _s, _t) { cout << #_l #_s "~" #_t #_r ": "; for (int _i = _s; _i != _t; ++_i) cout << _l _i _r << " "; cout << endl; }

#define N 50
int n, m, a[N + 1], b[N + 1], c[N + 1], l[N + 1], r[N + 1];

int f(int i, int x) {
	return a[i] * x * x + b[i] * x + c[i];
}

#define NODE 20000
#define EDGE 100000
#define INFI 12345678
struct edge {
	int next, node, w;
} e[EDGE << 1 | 1];
int head[NODE + 1], tot = 1;

inline void addedge(int a, int b, int w) {
	e[++tot].next = head[a];
	head[a] = tot, e[tot].node = b, e[tot].w = w;
	e[++tot].next = head[b];
	head[b] = tot, e[tot].node = a, e[tot].w = 0;
}

int S, T, cnt = 0, st[N + 1], d[NODE + 1], q[NODE + 1], M = 0;

int node(int x, int v) {
	return st[x] + v - l[x];
}

bool bfs() {
	int h = 0, t = 0;
	for (int i = S; i <= T; ++i) d[i] = 0;
	d[S] = 1, q[t++] = S;
	while (h < t) {
		int cur = q[h++];
		for (int i = head[cur]; i; i = e[i].next) {
			if (!e[i].w) continue;
			int node = e[i].node;
			if (d[node]) continue;
			d[node] = d[cur] + 1;
			q[t++] = node;
		}
	}
	return d[T] != 0;
}

int dfs(int x, int inflow) {
	if (x == T) return inflow;
	int ret = inflow, flow;
	for (int i = head[x]; i; i = e[i].next) {
		if (!e[i].w) continue;
		int node = e[i].node;
		if (d[node] != d[x] + 1) continue;
		flow = dfs(node, min(e[i].w, ret));
		if (!flow) continue;
		ret -= flow, e[i].w -= flow, e[i ^ 1].w += flow;
		if (!ret) break;
	}
	if (ret == inflow) d[x] = -1;
	return inflow - ret;
}

int maxFlow() {
	int ret = 0;
	while (bfs())
		ret += dfs(S, INFI);
	return ret;
}

int main(int argc, char *argv[]) {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i] >> b[i] >> c[i];
	S = 0, T = 1;
	for (int i = 1; i <= n; ++i) {
		cin >> l[i] >> r[i];
		st[i] = T;
		T += r[i] - l[i] + 1 + 1;
		for (int j = l[i]; j <= r[i]; ++j)
			M = max(M, f(i, j));
	}
	for (int i = 1; i <= n; ++i) {
		addedge(S, st[i], INFI);
		for (int j = l[i]; j <= r[i]; ++j)
			addedge(node(i, j), node(i, j) + 1, M - f(i, j));
		addedge(node(i, r[i]) + 1, T, INFI);
	}
	for (int i = 1; i <= m; ++i) {
		int x, y, w;
		cin >> x >> y >> w;
		for (int j = l[x]; j <= r[x]; ++j)
			if (j - w >= l[y] && j - w <= r[y] + 1)
				addedge(node(x, j), node(y, j - w), INFI);
	}
	
	int ans = maxFlow();
	if (ans >= INFI) cout << "Invalid" << endl;
	else {
		ans = M * n - ans;
		cout << ans << endl;
	}
	
	return 0;
}
