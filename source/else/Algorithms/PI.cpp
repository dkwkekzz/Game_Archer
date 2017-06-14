#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int INF = 987654321;
int cashe[10002];
string N;

int classify(int a, int b) {
	string M = N.substr(a, b - a + 1);
	
	if (M == string(M.size(), M[0])) return 1;

	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	if (progressive && (M[1] - M[0]) == 1)
		return 2;
	
	bool alternative = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2]) alternative = false;
	if (alternative) return 4;
	
	if (progressive) return 5;

	return 10;
}

int memorized(int begin) {
	if (begin == N.size()) return 0;

	int &ret = cashe[begin];
	if (ret != -1) return ret;

	ret = INF;
	for (int L = 3; L <= 5; L++) {
		if (begin + L < N.size())
			ret = min(ret, memorized(begin + L) + classify(begin, begin + L - 1));
	}
}
