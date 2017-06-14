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
typedef unsigned long long uint64;
const int INF = 987654321, MAX_N = 95;
int n;
uint64 cache[MAX_N][2];

void input(){
	cin >> n;
}

uint64 solve(){
	cache[1][1] = 1;
	for (int i = 2; i <= n; i++){
		cache[i][0] = cache[i - 1][0] + cache[i - 1][1];
		cache[i][1] = cache[i - 1][0];
	}

	return cache[n][0] + cache[n][1];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	input();

	memset(cache, 0, sizeof(cache));
	cout << solve() << endl;

	return 0;
}
