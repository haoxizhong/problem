#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 100009;
const int maxv = 10000;
const int bsz = 100;
const int maxb = 103;

int n, m;
int a[maxn], vb[maxb][maxb], ve[maxb][maxb];
int xb[maxn], xe[maxn];
int i_buf[maxn * maxb * 2], tib;

void pre() {
	memset(ve, 0, sizeof(ve));
	memset(xe, 0, sizeof(xe));
	for (int i = 1; i <= n; ++ i)
		++ xe[a[i]];
	for (int i = 0; i <= maxv; ++ i) {
		xb[i] = tib;
		tib += xe[i];
		xe[i] = xb[i];
	}
	for (int i = 1; i <= n; ++ i)
		i_buf[xe[a[i]] ++] = i;
	for (int m = 1; m <= bsz; ++ m) {
		for (int i = 1; i <= n; ++ i)
			++ ve[m][a[i] % m];
		for (int i = 0; i < m; ++ i) {
			vb[m][i] = tib;
			tib += ve[m][i];
			ve[m][i] = vb[m][i];
		}
		for (int i = 1; i <= n; ++ i)
			i_buf[ve[m][a[i] % m] ++] = i;
	}
}

int queryb(int l0, int r0, int p, int k) {
	if (vb[p][k] == ve[p][k])
		return 0;
	int *x1 = lower_bound(i_buf + vb[p][k], i_buf + ve[p][k], l0);
	int *x2 = upper_bound(i_buf + vb[p][k], i_buf + ve[p][k], r0);
	return x2 - x1;
}

int querys(int v, int l0, int r0) {
	if (xb[v] == xe[v])
		return 0;
	int *x1 = lower_bound(i_buf + xb[v], i_buf + xe[v], l0);
	int *x2 = upper_bound(i_buf + xb[v], i_buf + xe[v], r0);
	return x2 - x1;
}

int querya(int l0, int r0, int p, int k) {
	int ans = 0;
	for (int i = k; i <= maxv; i += p)
		ans += querys(i, l0, r0);
	return ans;
}

int main() {
	freopen("light.in", "r", stdin);
	freopen("light.out", "w", stdout);

	scanf("%d%d", &n, &m);
	tib = 0;
	for (int i = 1; i <= n; ++ i)
		scanf("%d", a + i);
	pre();
	while (m --) {
		int l, r, p, k;
		scanf("%d%d%d%d", &l, &r, &p, &k);
		if (p <= bsz)
			printf("%d\n", queryb(l, r, p, k));
		else
			printf("%d\n", querya(l, r, p, k));
	}
}

