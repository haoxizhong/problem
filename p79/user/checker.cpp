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
    char *input = argv[1];
    char *output = argv[2];
    char *answer = argv[3];
    int score = atoi(argv[4]);
    char *result = argv[5];
    char *log = argv[6];

	FILE *logf = fopen(log,"w");
	FILE *scoref = fopen(result,"w");

	pair<vector<string>,string> in_pair = read(output);
	pair<vector<string>,string> out_pair = read(output);
	pair<vector<string>,string> ans_pair = read(answer);

	if (in_pair.second!=out_pair.second)
	{
		fprintf(scoref,"0");
		fprintf(logf,"Data Error\n");
		return 0;
	}

	if (in_pair.second!=ans_pair.second)
	{
		fprintf(scoref,"0");
		fprintf(logf,"Your output doesn't match the input\n");
		return 0;
	}

	int A = out_pair.first.size();
	int B = ans_pair.first.size();
	int id1 = 0 , id2 = 0;
	int len1 = 0 , len2 = 0;
	int C = 0;
	while (id1 < A && id2 < B)
	{
		if (len1 == len2 && out_pair.first[id1] == ans_pair.first[id2]) C++;
		if (len1 < len2)
		{
			len1 += out_pair.first[id1].size();
			id1++;
		}
		else
		{
			len2 += ans_pair.first[id2].size();
			id2++;
		}
	}
	double D = 1.0 * C / B;
	double E = 1.0 * C / A;
	double F = 2.0 * D * E / ( D + E );
	fprintf(logf,"A=%d\n",A);
	fprintf(logf,"B=%d\n",B);
	fprintf(logf,"C=%d\n",C);
	fprintf(logf,"D=%lf\n",D);
	fprintf(logf,"E=%lf\n",E);
	fprintf(logf,"F=%lf\n",F);

	double s = 0;
	if (F>0.75) s = (F - 0.75) / 0.25 * score;
	fprintf(scoref,"%.0lf\n",s);

    return 0;
}
