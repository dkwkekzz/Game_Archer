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
int score[MAX_N][2];
int C[MAX_N][2];

void input(){
	cin >> n;
	for (int i = 0; i < n; i++) cin >> score[i][0];
	for (int i = 0; i < n; i++) cin >> score[i][1];
}

int solve(){
	C[0][0] = score[0][0];
	C[0][1] = score[0][1];
	for (int i = 1; i < n; i++){
		C[i][0] = max(C[i - 1][1] + score[i][0], C[i - 1][0]);
		C[i][1] = max(C[i - 1][0] + score[i][1], C[i - 1][1]);
	}

	return max(C[n - 1][0], C[n - 1][1]);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << solve() << endl;
	}

	return 0;
}