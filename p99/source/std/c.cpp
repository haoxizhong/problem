#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define LL long long 
#ifdef unix
#define RE "%lld"
#else
#define RE "%I64d"
#endif
using namespace std;
const int VAL = 10050, MAXN = 55, mo = 1e9 + 9;
int n, m, a[VAL], b[VAL];
int c[MAXN][MAXN];
void init_c(int n) {
	for (int i = 0; i <= n; ++ i) 
		c[i][0] = c[i][i] = 1;
	for (int i = 1; i <= n; ++ i) 
		for (int j = 1; j < n; ++ j) 
			c[i][j] = (c[i-1][j-1] + c[i-1][j]) % mo;
}
int modpow(int a, int b) {
	int res = 1, q = a;
	while (b) {
		if (b & 1) res = 1ll * res * q % mo;
		q = 1ll * q * q % mo;
		b >>= 1;
	}
	return res;
}
int calc(int n, int m, int nn, int mm, int h) {
	int res = 0;
	for (int i = 0; i <= nn; ++ i) 
		for (int j = 0; j <= mm; ++ j) {
			int tmp = 1ll * modpow(h, n * m - (n - i) * (m - j)) * modpow(h+1,(n-i)*(m-j)-(n-nn)*(m-mm)) % mo
					  * c[nn][i] % mo * c[mm][j] % mo;
			if ((i + j) & 1) res = ((res - tmp) % mo + mo ) % mo;
			else {
				res += tmp; if (res >= mo) res -= mo; }
		}
	return res;	
}	
int main() {
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1, x; i <= n; ++ i) 
		scanf("%d", &x), a[x] ++;
	for (int i = 1, x; i <= m; ++ i) 
		scanf("%d", &x), b[x] ++;
	init_c(max(n, m));
	LL res = 1;
	int nown = 0, nowm = 0;
	for (int i = 10000; i >= 0; -- i)
	   if (a[i] || b[i]) {
			nown += a[i], nowm += b[i];
			res = 1ll * res * calc(nown, nowm, a[i], b[i], i) % mo;
	   }	   
	printf(RE"\n", res);
	return 0;
}
