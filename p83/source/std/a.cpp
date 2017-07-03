#define PRID "la"
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long dint;
#define _l (long long int)
#ifdef WIN32
#	define lld "%I64d"
#else
#	define lld "%lld"
#endif

const int mod = 998244353;
const int maxn = 503;

int n, k, a[maxn][maxn], l[maxn], b[maxn][maxn], c[maxn][maxn];

int modPow(int a, int x) {
	int s(1);
	for (a %= mod; x; x >>= 1, a = _l a * a % mod) {
		if (x & 1) {
			s = _l s * a % mod;
		}
	}
	return s;
}

void getEigenMatrix() {
	for (int i = 0; i < n; ++ i) {
		b[i][i] = 1;
		for (int j = i - 1; j >= 0; -- j) {
			int s(0), m(modPow(l[i] - a[j][j] + mod, mod - 2));
			for (int k = j + 1; k <= i; ++ k) {
				s = (s + _l a[j][k] * b[k][i])% mod;
			}
			b[j][i] = _l s * m % mod;
		}
	}
}

void jordanEliminate() {
	for (int i = n - 1; i >= 0; -- i) {
		c[i][i] = modPow(b[i][i], mod - 2);
		for (int j = 0; j < i; ++ j) {
			int e(_l b[j][i] * modPow(b[j][j], mod - 2) % mod);
			for (int k = i; k < n; ++ k) {
				c[j][k] -= _l c[i][k] * e % mod;
				if (c[j][k] < 0) {
					c[j][k] += mod;
				}
			}
		}
	}
}

void reform() {
	for (int i = 0; i < n; ++ i) {
		for (int j = i; j < n; ++ j) {
			b[i][j] = _l b[i][j] * l[j] % mod;
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = i; j < n; ++ j) {
			a[i][j] = 0;
			for (int k = i; k <= j; ++ k) {
				a[i][j] = (a[i][j] + _l b[i][k] * c[k][j])% mod;
			}
		}
	}
}

int main() {

	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			scanf("%d", a[i] + j);
		}
		l[i] = a[i][i];
	}
	getEigenMatrix();
	jordanEliminate();
	for (int i = 0; i < n; ++ i) {
		l[i] = modPow(l[i], k);
	}
	reform();
	dint sum(0);
	int xs(0);
	for (int i = 0; i < n; ++ i) {
		for (int j = i; j < n; ++ j) {
			sum += a[i][j];
			xs ^= a[i][j];
		}
	}
	printf(lld " %d\n", sum, xs);
}

