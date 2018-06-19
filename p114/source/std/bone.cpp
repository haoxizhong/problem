#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>

using namespace std;

const int MAXM = 32,MAXL = 32;

struct trie_t
{
  struct node
  {
    node *nxt[2],*fail,*trans[2],*pre;
    bool end;
  } buf[MAXM * MAXL],*top,*root;
  
  trie_t()
  {
    memset(buf,0,sizeof(buf));
    top = buf;
    root = newnode();
  }

  node* newnode()
  {
    return top++;
  }

  void insert(const char *str)
  {
    node *cur = root;
    for(const char *ch = str; *ch != '\0'; ch++)
      {
	if (cur->nxt[*ch - '0'] == NULL)
	  {
	    cur->nxt[*ch - '0'] = newnode();
	    cur->nxt[*ch - '0']->pre = cur;
	  }
	cur = cur->nxt[*ch - '0'];
      }
    cur->end = true;
  }

  void build()
  {
    queue<node *> que;
    que.push(root);
    
    while(!que.empty())
      {
	node *x = que.front();
	que.pop();

	for(int c = 0; c < 2; c++)
	  if (x->nxt[c] != NULL)
	    {
	      que.push(x->nxt[c]);

	      if (x->fail == NULL) x->nxt[c]->fail = root;
	      else x->nxt[c]->fail = x->fail->trans[c];
	      
	      x->trans[c] = x->nxt[c];
	    }
	  else
	    x->trans[c] = x->fail == NULL ? root : x->fail->trans[c];

	if (x->fail)
	  x->end |= x->fail->end;//Check 0459
      }
  }

  int get_id(node *x) const
  {
    return x - buf;
  }

  int get_string(node *x,char *str) const
  {
    int res = 0;
    for(;x != root; x = x->pre)
      {
	str[res++] = (x->pre->nxt[1] == x);
      }
    reverse(str,str + res);
    return res;
  }

  node *get_node(int len,const char *str) const
  {
    node *x = root;
    for(int i = 0; i < len; i++) x = x->trans[str[i]];	
    return x;
  }

  bool get_match(int len,const char *str) const
  {
    node *x = root;
    for(int i = 0; i < len; i++)
      {
	x = x->trans[str[i]];
	if (x->end) return true;
      }
    return false;
  }

  void make_st(const trie_t &res);
  void make_st_2(const trie_t &res);
} trie,trie_rev;

char str[MAXL];

typedef pair<trie_t::node *,trie_t::node *> state;
vector< pair<trie_t::node *,trie_t::node *> > st_list;
int pos[MAXM * MAXL][MAXM * MAXL];

void trie_t::make_st(const trie_t &rev)
{
  for(trie_t::node *x = root; x < top; x++)
    {
      int len = get_string(x,str);

      for(int l = 0; l <= len; l++)
	{
	  trie_t::node *y = rev.get_node(l,str + len - l);

	  if (pos[get_id(x)][rev.get_id(y)] == -1)
	    {
	      pos[get_id(x)][rev.get_id(y)] = st_list.size();
	      st_list.push_back(make_pair(x,y));
	    }
	}
    }
}

void trie_t::make_st_2(const trie_t &rev)
{
  for(trie_t::node *x = root; x < top; x++)
    {
      int len = get_string(x,str);

      for(int l = 0; l <= len; l++)
	{
	  trie_t::node *y = rev.get_node(l,str + len - l);
	  //printf("%d %d %d %d\n",len,l,str[0],rev.get_id(y));

	  if (pos[rev.get_id(y)][get_id(x)] == -1)
	    {
	      pos[rev.get_id(y)][get_id(x)] = st_list.size();
	      st_list.push_back(make_pair(y,x));
	    }
	}

    }
}

const int mod = 1000000007;
typedef int arr[2][MAXM * MAXL * MAXL * 2];

arr dp[2];

void add(int &a,const int &b)
{
  a = (a + b) % mod;
}

int get_pos(const state &x)
{
  return pos[trie.get_id(x.first)][trie_rev.get_id(x.second)];
}

pair<int,int> get_trans(const state &s,char c)
{
  state nst(s.first->trans[c],s.second->trans[c]);
  const int dk = nst.first->end + nst.second->end;
  
  if (nst.first->end)
    nst.first = trie.root;
  if (nst.second->end)
    nst.second = trie_rev.root;
      
  return make_pair(dk,get_pos(nst));
}

pair<int,int> trans[MAXM * MAXL * MAXL * 2][2];

int slen[MAXM],plen[MAXM];


bool get_match(const state &st)//Check 0450
{
  static char str[MAXL * 2];
  int l1 = trie.get_string(st.first,str);
  int l2 = trie_rev.get_string(st.second,str + l1) + l1;
  reverse(str + l1,str + l2);
  //for(int i = 0; i < l2; i++) printf("%d",str[i]);
  //puts("****");
  return trie.get_match(l2,str);
}

int main()
{
  
  int n,m;
  scanf("%d%d",&n,&m);
  
  for(int i = 0; i < m; i++)
    {
      scanf("%s",str);
      int len = strlen(str);
      trie.insert(str);
      reverse(str,str + len);
      trie_rev.insert(str);
      slen[i] = len; 
    }

  trie.build(),trie_rev.build();
  memset(pos,-1,sizeof(pos));
  
  trie.make_st(trie_rev);
  trie_rev.make_st_2(trie);

  int lap = 0;
  memset(dp[lap],0,sizeof(dp[lap]));
  dp[lap][0][0] = 1;
  
  const int stot = st_list.size();

  for(int j = 0; j < stot; j++)
    {
      //match[j] = get_match(st_list[j]);
      for(int c = 0; c < 2; c++)
	trans[j][c] = get_trans(st_list[j],c);
      //printf("St %d (%d,%d)\n",j,trie.get_id(st_list[j].first),trie_rev.get_id(st_list[j].second));
    }
  
  for(int i = 0; i < n / 2; i++)
    {
      arr &pre = dp[lap],&cur = dp[lap ^ 1];
      fill(cur[0],cur[0] + stot,0);
      fill(cur[1],cur[1] + stot,0);

      for(int k = 0; k < 2; k++)
	for(int j = 0; j < stot; j++)
	  if (pre[k][j] != 0)
	  {
	    //printf("%d (%d,%d) %d\n",k,trie.get_id(st_list[j].first),trie_rev.get_id(st_list[j].second),pre[k][j]);
	    for(int c = 0; c < 2; c++)
	      {
		if (k + trans[j][c].first < 2)
		  add(cur[k + trans[j][c].first][trans[j][c].second],pre[k][j]);
	      }
	  }
      
      lap ^= 1;
      //puts("--------");
    }

  int ans = 0;
  if (n & 1)
    {
      for(int k = 0; k < 2; k++)
	for(int j = 0; j < stot; j++)
	  {
	    for(int c = 0; c < 2; c++)
	      {
		bool m = get_match(state(st_list[j].first,st_list[j].second->trans[c]));//Check
		if (m + k < 2)
		  {
		    add(ans,dp[lap][k][j]);
		  }
	      }
	  }
    }
  else
    {
      for(int k = 0; k < 2; k++)
	for(int j = 0; j < stot; j++)
	  if (dp[lap][k][j])
	  {
	    bool m = get_match(st_list[j]);
	    //printf("%d (%d,%d) %d\n",m + k,trie.get_id(st_list[j].first),trie_rev.get_id(st_list[j].second),dp[lap][k][j]);
	    if (m + k < 2) add(ans,dp[lap][k][j]);
	  }
    }

  printf("%d\n",ans);
  return 0;
}
