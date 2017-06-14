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
const int INF = 987654321, MAX_N = 101, MAX_K = 10001;
int n, k;
int K[MAX_N];

void input(){
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> K[i];
}

int solve(){
	vector<int> coin(MAX_K, INF);
	coin[0] = 0;
	for (int i = 1; i <= k; i++){
		for (int j = 0; j < n; j++){
			if (i - K[j] >= 0) coin[i] = min(coin[i], coin[i - K[j]] + 1);
		}
	}

	return coin[k] == 0 ? -1 : coin[k];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	input();

	cout << solve() << endl;

	return 0;
}