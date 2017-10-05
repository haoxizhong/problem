#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

#define get(a,b,c) ((a-1)*12+(b-1)*4+c)

int en,tmp[4][4],color[37],map[9][5],q[37],nowmap[4][4],newmap[4][4];

bool num[9],use[90000000],right[37],row[4],col[4],col_find[5];

char s[10];

struct rec
{
	int sta,step;
	rec(){}
	rec(int a,int b)
	{
		sta=a;step=b;
	}
};

queue<rec> que;

struct edge
{
	int e;
	edge *next;
}*v[37],ed[100];

void add_edge(int s,int e)
{
	en++;
	ed[en].next=v[s];v[s]=ed+en;v[s]->e=e;
	en++;
	ed[en].next=v[e];v[e]=ed+en;v[e]->e=s;
}

bool check(int nows)
{
	memset(num,false,sizeof(num));
	for (int a=3;a>=1;a--)
		for (int b=3;b>=1;b--)
			if (a!=3 || b!=3)
			{
				tmp[a][b]=nows%10;
				num[nows%10]=true;
				nows/=10;
			}
	for (int a=0;a<9;a++)
		if (!num[a])
		{
			tmp[3][3]=a;
			break;
		}
	int cnt=0;
	for (int a=1;a<=3;a++)
		for (int b=1;b<=3;b++)
			for (int c=1;c<=4;c++)
			{
				cnt++;
				color[cnt]=map[tmp[a][b]][c];
			}
	memset(right,false,sizeof(right));
	memset(col_find,false,sizeof(col_find));
	for (int a=1;a<=36;a++)
		if (!right[a])
		{
			if (col_find[color[a]]) return false;
			col_find[color[a]]=true;
			int front=1,tail=1;
			q[1]=a;
			right[a]=true;
			for (;front<=tail;)
			{
				int now=q[front++];
				for (edge *e=v[now];e;e=e->next)
					if (color[e->e]==color[now] && !right[e->e])
					{
						right[e->e]=true;
						q[++tail]=e->e;
					}
			}
		}
	return true;
}

int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);

	for (int a=1;a<=3;a++)
		for (int b=1;b<=3;b++)
		{
			add_edge(get(a,b,1),get(a,b,3));
			add_edge(get(a,b,1),get(a,b,4));
			add_edge(get(a,b,2),get(a,b,3));
			add_edge(get(a,b,2),get(a,b,4));
			if (a!=3) add_edge(get(a,b,2),get(a+1,b,1));
			if (b!=3) add_edge(get(a,b,4),get(a,b+1,3));
		}
	int cnt=0;
	for (int a=1;a<=3;a++)
		for (int b=1;b<=3;b++)
		{
			scanf("%s",s+1);
			for (int c=1;c<=4;c++)
				if (s[c]=='R') map[cnt][c]=0;
				else 
				{
					if (s[c]=='G') map[cnt][c]=1;
					else
					{
						if (s[c]=='B') map[cnt][c]=2;
						else map[cnt][c]=3;
					}
				}
			if (s[5]=='1') row[a]=col[b]=true;
			cnt++;
		}
	int nows=1234567;
	if (check(nows))
	{
		printf("0\n");
		return 0;
	}
	que.push(rec(nows,0));
	use[nows]=true;
	rec now;
	while (que.size())
	{
		now=que.front();
		que.pop();
		int step=now.step;
		int nows=now.sta;
		memset(num,false,sizeof(num));
		for (int a=3;a>=1;a--)
			for (int b=3;b>=1;b--)
				if (a!=3 || b!=3)
				{
					nowmap[a][b]=nows%10;
					num[nows%10]=true;
					nows/=10;
				}
		for (int a=0;a<9;a++)
			if (!num[a])
			{
				nowmap[3][3]=a;
				break;
			}
		int news=0;
		for (int a=1;a<=3;a++)
		{
			if (!row[a])
			{
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						newmap[b][c]=nowmap[b][c];
				int x=newmap[a][1];
				newmap[a][1]=newmap[a][2];newmap[a][2]=newmap[a][3];newmap[a][3]=x;
				news=0;
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						if (b!=3 || c!=3) news=news*10+newmap[b][c];
				if (!use[news])
				{
					use[news]=true;
					if (check(news))
					{
						printf("%d\n",step+1);
						return 0;
					}
					que.push(rec(news,step+1));
				}
				x=newmap[a][1];
				newmap[a][1]=newmap[a][2];newmap[a][2]=newmap[a][3];newmap[a][3]=x;
				news=0;
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						if (b!=3 || c!=3) news=news*10+newmap[b][c];
				if (!use[news])
				{
					use[news]=true;
					if (check(news))
					{
						printf("%d\n",step+1);
						return 0;
					}
					que.push(rec(news,step+1));
				}
			}
			if (!col[a])
			{
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						newmap[b][c]=nowmap[b][c];
				int x=newmap[1][a];
				newmap[1][a]=newmap[2][a];newmap[2][a]=newmap[3][a];newmap[3][a]=x;
				news=0;
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						if (b!=3 || c!=3) news=news*10+newmap[b][c];
				if (!use[news])
				{
					use[news]=true;
					if (check(news))
					{
						printf("%d\n",step+1);
						return 0;
					}
					que.push(rec(news,step+1));
				}
				x=newmap[1][a];
				newmap[1][a]=newmap[2][a];newmap[2][a]=newmap[3][a];newmap[3][a]=x;
				news=0;
				for (int b=1;b<=3;b++)
					for (int c=1;c<=3;c++)
						if (b!=3 || c!=3) news=news*10+newmap[b][c];
				if (!use[news])
				{
					use[news]=true;
					if (check(news))
					{
						printf("%d\n",step+1);
						return 0;
					}
					que.push(rec(news,step+1));
				}
			}
		}
	}

	return 0;
}
