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
const int INF = 987654321, MAX_N = 1000001;
int n;

void input(){
	cin >> n;
}

int solve(vector<int>& cache){
	cache[1] = 0;
	for (int i = 1; i < n; i++){
		cache[i * 3] = min(cache[i * 3], cache[i] + 1);
		cache[i * 2] = min(cache[i * 2], cache[i] + 1);
		cache[i + 1] = min(cache[i + 1], cache[i] + 1);
	}

	return cache[n];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	input();

	vector<int> cache(n * 3 + 1, INF);
	cout << solve(cache) << endl;

	return 0;
}