#include <cstdio>
#include <cstring>
#include <algorithm>
 
using namespace std;
 
typedef pair <int, int> ipr;
 
const int maxn = 300009;
 
int n, a[maxn], pr[maxn], s[maxn];
ipr t[maxn];
 
int main() {
    scanf("%d%*d", &n);
    ++ n;
    for (int i = 0; i < n; ++ i) {
        scanf("%d", a + i);
        t[i] = ipr(a[i], i);
    }
    sort(t, t + n);
    for (int i = 0; i < n; ++ i)
        pr[t[i]. second] = i;
    for (int i = n - 1, p = 0; i >= 0; -- i) {
        s[i] = a[p];
        p = pr[p];
    }
    for (int i = 1; i < n; ++ i)
        printf("%d ", s[i]);
    putchar(10);
}
