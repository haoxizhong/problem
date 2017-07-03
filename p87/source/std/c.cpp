#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cctype>

using namespace std;

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
   
#define readint(_n_) \
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


const int maxn = 1000010;

int z[maxn], top, n, right;
pair<int, int> sufmax[maxn];

int l=0;

char s[maxn*7];

void print(int x)
{
	int c=0,v=0;
	for (;x;)
	{
		v=v*10+x%10;
		c++;
		x/=10;
	}
	for (;c--;)
	{
		s[l++]=v%10+'0';
		v/=10;
	}
	s[l++]=' ';
}

int main() {
	right = 1;
	readint(n);
	for (int i = 1; i <= n; ++ i)
	{
		readint(z[i]);
	}
	for (int i = n; i; -- i) {
		int pos = z[i] > sufmax[i + 1].first ? i : sufmax[i + 1].second;
		sufmax[i] = make_pair(z[pos], pos);
	}
	for (int i = 1; i <= n; ++ i) {
		if (z[top] > sufmax[right].first) {
			print(z[top]);
		} else {
			print(z[sufmax[right].second]);
			top = sufmax[right].second;
			right = top + 1;
		}
		z[top] = 0;
		while (top && !z[top]) top --;
	}
	printf("%s\n",s);
	return 0;
}
