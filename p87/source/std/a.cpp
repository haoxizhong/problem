#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

stack<int> s;

queue<int> q;

priority_queue<int> h;

int n;

int main()
{
	scanf("%d",&n);
	bool able1=true,able2=true,able3=true;
	int z=0;
	for (;n--;)
	{
		int o,v;
		scanf("%d%d",&o,&v);
		if (o&1)
		{
			s.push(v);
			q.push(v);
			h.push(v);
			z++;
		}
		else
		{
			if (!z)
			{
				able1=able2=able3=false;
				break;
			}
			z--;
			if (s.top()!=v) able1=false;
			if (q.front()!=v) able2=false;
			if (h.top()!=v) able3=false;
			s.pop();
			q.pop();
			h.pop();
		}
	}
	printf("%s\n",able1 ? "YES" : "NO");
	printf("%s\n",able2 ? "YES" : "NO");
	printf("%s\n",able3 ? "YES" : "NO");

	return 0;
}
