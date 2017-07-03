#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2000;
const int maxm = 160010;

int len;
char str[maxm * maxn];
struct Node {
	char type;
	Node *next, *last;
	Node (char c) {
		type = c;
		next = last = NULL;
	}
}*head, *tail;

int main() {
	head = tail = NULL;
	int n;
	char c;
	while (1) {
		scanf("%c", &c);
		if (c == '\n') break;
		Node *n = new Node(c);
		n -> last = tail;
		if (tail) tail -> next = n;
		tail = n;
		if (!head) head = n;
	}
	len = 0;
	scanf("%d", &n);
	while (n--) {
		int pos;
		char t[3];
		scanf("%d %s", &pos, t);
		Node *now = head;
		for (int i = 0; i < pos; ++ i)
			now = now -> next;
		//insert
		Node *newnode = new Node(t[0]);
		if (!head && !tail) {
			head = tail = newnode;
		} else {
			newnode -> next = now;
			if (now) {
				newnode -> last = now -> last;
				if (now -> last) now -> last -> next = newnode;
				else head = newnode;
				now -> last = newnode;
			}
			else {
				tail -> next = newnode;
				newnode -> last = tail;
				tail = newnode;
			}
		}
		//modify
		while (1) {
			while (newnode -> next && newnode -> type == newnode -> next -> type) newnode = newnode -> next;
			int cnt = 1;
			while (newnode -> last && newnode -> type == newnode -> last -> type)
				cnt ++, newnode = newnode -> last;
			if (cnt > 2) {
				while (cnt --) {
					if (newnode -> last) newnode -> last -> next = newnode -> next;
					if (newnode -> next) newnode -> next -> last = newnode -> last;
					Node *tmp = newnode;
					if (head == newnode) head = head -> next;
					if (newnode -> next) newnode = newnode -> next;
					else {
						newnode = newnode -> last;
						tail = newnode;
					}
					delete tmp;
				}
			} else break;
			if (!newnode) {
				head = tail = NULL;
				break;
			}
		}
		if (!head) str[len++] = '-', str[len++] = '\n';
			//puts("-");
		else {
			for (Node *p = head; p; p = p -> next)
				str[len++] = p -> type;
				//printf("%c", p->type);
			str[len++] = '\n';
			//puts("");
		}
	}
	printf("%s", str);
	return 0;
}
