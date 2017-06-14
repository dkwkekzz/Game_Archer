#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int MAX_N = 10 + 5, MAX_M = 2000 + 5;
int t, n, m;
int64 cache[MAX_M][MAX_N], C[MAX_N][MAX_M];

int64 lotto(int prior, int counter){
	if (counter == n) return 1;

	int64 &ret = cache[prior][counter];
	if (ret != -1) return ret;

	ret = 0;
	for (int current = prior * 2; current <= m; current++){
		if (current) ret += lotto(current, counter + 1);
	}
	return ret;
}

int64 solve(){
	int64 ret = 0;
	for (int i = 1; i <= m; i++) ret += C[n][i];
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(C, 0, sizeof(C));
	for (int current = 1; current <= 2000; current++){
		for (int counter = 1; counter <= 10; counter++){
			if (counter == 1) C[counter][current] = 1;
			for (int next = current * 2; next <= 2000; next++){
				C[counter + 1][next] += C[counter][current];
			}
		}
	}
	cin >> t;
	for (int tc = 0; tc < t; tc++){
		memset(cache, -1, sizeof(cache));
		cin >> n >> m;
		cout << lotto(0, 0) << endl;
		cout << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}