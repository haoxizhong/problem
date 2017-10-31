#define PROC "shana"
#include <cstdio>
#include <cctype>
#include <memory.h>
#include <algorithm>
#include<cctype>

using namespace std;

typedef long long qw;

#define _l (qw)
const int BUF_SIZE = 30;
char buf[BUF_SIZE], *buf_s = buf, *buf_t = buf + 1;
  
#define PTR_NEXT() \
    { \
        buf_s ++; \
        if (buf_s == buf_t) \
        { \
            buf_s = buf; \
            buf_t = buf + fread(buf, 1, BUF_SIZE, stdin); \
        } \
    }
   
#define readInt(_n_) \
    { \
        while (*buf_s != '-' && !isdigit(*buf_s)) \
            PTR_NEXT(); \
        bool register _nega_ = false; \
        if (*buf_s == '-') \
        { \
            _nega_ = true; \
            PTR_NEXT(); \
        } \
        int register _x_ = 0; \
        while (isdigit(*buf_s)) \
        { \
            _x_ = _x_ * 10 + *buf_s - '0'; \
            PTR_NEXT(); \
        } \
        if (_nega_) \
            _x_ = -_x_; \
        (_n_) = (_x_); \
    }

const int maxn = 50010;
const int maxl = 31;
const int maxnd = maxn * maxl;
const int mod = 1e9 + 7;
const int inv = 500000004;

int v0, n, rt, tn, a[maxn];
int tr[maxnd][2], rb[maxnd][maxl], c[maxnd];
qw k;

void trieIns(int v) {
	int p = rt;
	for (int i = maxl - 1; i >= 0; -- i) {
		int v0 = (v >> i) & 1;
		if (!tr[p][v0])
			tr[p][v0] = ++ tn;
		p = tr[p][v0];
		++ c[p];
		for (int j = maxl - 1; j >= 0; -- j)
			if ((v >> j) & 1)
				++ rb[p][j];
	}
}

int cntUpper(int v, int vu) {
	int p = rt, s = 0;
	for (int i = maxl - 1; i >= 0; -- i) {
		int v0 = (v >> i) & 1;
		if ((vu >> i) & 1) {
			p = tr[p][v0 ^ 1];
		}
		else {
			s += c[tr[p][v0 ^ 1]];
			p = tr[p][v0];
		}
	}
	return s;
}

qw check(int v) {
	qw s = 0;
	for (int i = 0; i < n; ++ i)
		s += cntUpper(a[i], v);
	return s >> 1;
}

int sumUpper(int v, int vu) {
	int s = 0, p = rt;
	for (int i = maxl - 1; i >= 0; -- i) {
		int v0 = (v >> i) & 1;
		if ((vu >> i) & 1)
			p = tr[p][v0 ^ 1];
		else {
			for (int j = 0; j < maxl; ++ j)
				if ((v >> j) & 1)
					s = (_l s + (1LL << j) * (_l c[tr[p][v0 ^ 1]] - _l rb[tr[p][v0 ^ 1]][j])) % mod;
				else
					s = (_l s + (1LL << j) * _l rb[tr[p][v0 ^ 1]][j]) % mod;
			p = tr[p][v0];
		}
	}
	return s;
}

int main() {
	freopen("war.in", "r", stdin);
	freopen("war.out", "w", stdout);

	readInt(n);
	readInt(k);
	rt = 1;
	tn = 1;
	for (int i = 0; i < n; ++ i) {
		readInt(a[i]);
		trieIns(a[i]);
	}
	{
		int l = 0, r = 2147483647;
		while (l < r) {
			int mid = (_l l + r + 1) >> 1;
			if (check(mid - 1) < k)
				r = mid - 1;
			else
				l = mid;
		}
		v0 = l;
	}
	if (v0) {
		//printf("%d %lld\n", v0, check(v0));
		int ans = 0;
		for (int i = 0; i < n; ++ i)
			ans = (_l ans + sumUpper(a[i], v0 - 1)) % mod;
		ans = (_l ans * inv % mod + ((k - check(v0 - 1)) % mod + mod) * _l v0) % mod;
		printf("%d\n", ans);
	}
	else {
		int ans = 0;
		for (int i = 0; i < n; ++ i)
			ans = (_l ans + sumUpper(a[i], 0)) % mod;
		ans = _l ans * inv % mod;
		printf("%d\n", ans);
	}
}
