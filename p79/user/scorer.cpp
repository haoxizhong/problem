#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

char djm[1000];

char s[10000000];

pair<vector<string>,string> read(char *filename)
{
	FILE* inf = fopen(filename,"r");
	string str;
	string res = "";
	vector<string> arr;
	int cnt=0;
	while (~fscanf(inf,"%s",s))
	{
		arr.push_back(string(s));
		res = res + str;
	}
	return make_pair(arr,res);
}

int main(int argc, char *argv[]) {
	if (read(argv[1]).second != read(argv[2]).second) printf("Never, you will never get score.");
	else printf("OK, you may get score now.");

	return 0;
}
