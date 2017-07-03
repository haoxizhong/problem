#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#ifdef unix
#define FMT "%lld"
#else
#define FMT "%I64d"
#endif

typedef long long ll;
const int kMod = 1000000007;
const int kSize = 180;
int n, p, q;
ll m;

struct State {
	int cnt[3], ill;
	State() {}
	State(int a, int b, int c, int d) {
		cnt[0] = a, cnt[1] = b, cnt[2] = c, ill = d;
	}
} state[kSize], cur;
int re[11][11][11][5], idx;

struct Matrix {
	int v[kSize][kSize];
	void clear() {
		memset(v, 0, sizeof(v));
	}
	Matrix() {
		clear();
	}
} trans, init, e, ans, res, tmp;

#define INC(x, y) { \
	(x) += (y); \
	if ((x) >= kMod) (x) -= kMod; \
}

Matrix operator * (const Matrix &a, const Matrix &b) {
	static Matrix c;
	c.clear();
	for (int i = 0; i < idx; ++ i)
		for (int k = 0; k < idx; ++ k) if (a.v[i][k])
			for (int j = 0; j < idx; ++ j)
				INC(c.v[i][j], (ll)a.v[i][k] * b.v[k][j] % kMod);
	return c;
}

void Power(ll b) {
	while (b) {
		if (b & 1) res = res * tmp;
		b >>= 1;
		tmp = tmp * tmp;
	}
}

void Dfs(int step, int sum) {
	if (step == p) {
		if (!sum) {
			for (int i = 0; i <= q; ++ i) {
				cur.ill = i;
				re[cur.cnt[0]][cur.cnt[1]][cur.cnt[2]][cur.ill] = idx;
				state[idx ++] = cur;
			}
		}
	}
	else
		for (int i = 0; i <= sum; ++ i) {
			cur.cnt[step] = i;
			Dfs(step + 1, sum - i);
		}
}

int main() {
	scanf("%d" FMT "%d%d", &n, &m, &p, &q);
	memset(re, -1, sizeof(re)), idx = 0, Dfs(0, n);
	for (int i = 0; i < idx; ++ i) {
		State u = state[i];
		for (int msk = (u.ill == q); msk < (1 << n); ++ msk) {
			State v(0, 0, 0, u.ill + (msk == 0));
			bool fail = false;
			for (int k = 0; k < n && !fail; ++ k) {
				int o = msk >> k & 1;
				for (int r = 0, s = 0; r < p; ++ r) {
					s += u.cnt[r];
					if (k < s) {
						if (o)
							++ v.cnt[0];
						else {
							if (r + 1 == p)
								fail = true;
							else
								++ v.cnt[r + 1];
						}
						break;
					}
				}
			}
			if (!fail) {
				int j = re[v.cnt[0]][v.cnt[1]][v.cnt[2]][v.ill];
				++ trans.v[j][i];
			}
		}
	}
	for (int i = 0; i < idx; ++ i) e.v[i][i] = 1;
	res = e, tmp = trans;
	Power(m - 1);
	for (int msk = (q == 0); msk < (1 << n); ++ msk) {
		State u(0, 0, 0, (msk == 0));
		bool fail = false;
		for (int k = 0; k < n && !fail; ++ k) {
			int o = msk >> k & 1;
			if (o)
				++ u.cnt[0];
			else {
				if (1 == p)
					fail = true;
				else
					++ u.cnt[1];
			}
		}
		if (!fail) {
			int i = re[u.cnt[0]][u.cnt[1]][u.cnt[2]][u.ill];
			init.v[i][0] ++;
		}
	}
	ans = res * init;
	int sum = 0;
	for (int i = 0; i < idx; ++ i)
		INC(sum, ans.v[i][0]);
	printf("%d\n", sum);
	return 0;
}
