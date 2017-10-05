#define PROC "a"
#include <cstdio>
#include <ctype.h>
#include <memory.h>

const int maxn = 40010;

int nextInt() {
	int d, s = 0;
	do
		d = getchar();
	while (!isdigit(d));
	do
		s = s * 10 + d - 48, d = getchar();
	while (isdigit(d));
	return s;
}

int n, c[maxn], a, b, s;

int main() {
#ifndef ONLINE_JUDGE
	freopen(PROC ".in", "r", stdin);
	freopen(PROC ".out", "w", stdout);
#endif

	memset(c, 0, sizeof(c));
	n = nextInt();
	s = 0;
	while (n --) {
		a = nextInt();
		b = nextInt();
		if (a == 1) {
			int i;
			for (i = 1; i * i < b; i ++)
				if (b % i == 0)
					c[i] ++, c[b / i] ++;
			if (i * i == b)
				c[i] ++;
		}
		else
			s ^= c[b];
	}
	printf("%d\n", s);
}
