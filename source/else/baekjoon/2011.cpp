#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
using namespace std;

const int INF = 987654321, MAX_N = 5005, MOD = 1000000;

int solve(const string& s){
	int C[MAX_N]; memset(C, 0, sizeof(C));
	C[0] = 1;
	for (int i = 0; i < s.size(); i++){
		if (s[i] - '0' == 0) continue;
		C[i + 1] = (C[i] + C[i + 1]) % MOD;
		if ((s[i] - '0') < 2 || ((s[i] - '0') == 2 && (s[i + 1] - '0') < 7)) 
			C[i + 2] = (C[i] + C[i + 2]) % MOD;
	}

	return C[s.size()];
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	string s;
	cin >> s;
	cout << solve(s) << endl;

	return 0;
}