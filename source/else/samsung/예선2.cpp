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

const int MAX_N = 50000, MOD = 1000000009;
int n, k, l;
int L[MAX_N + 1];
int board[MAX_N + 1][101];

void input(){
	cin >> n >> k >> l;
	for (int i = 0; i < l; i++){
		int temp; cin >> temp;
		L[temp] = 1;
	}
}

int solve(){
	for (int i = 1; i <= k; i++) board[i][i]++;
	for (int i = 1; i < n; i++){
		if (L[i]) continue;
		for (int k1 = 1; k1 <= k; k1++){
			int jump = board[i][k1];
			if (jump){
				for (int k2 = 1; k2 <= k; k2++){
					if (k1 == k2) continue;
					board[i + k2][k2] = (board[i + k2][k2] + jump) % MOD;
				}
			}
		}
	}
	int ret = 0;
	for (int i = 1; i <= k; i++) ret = (ret + board[n][i]) % MOD;

	for (int j = 1; j <= k; j++){
		cout << "k: " << j << " // ";
		for (int i = 0; i <= n; i++){
			cout << board[i][j] << " | ";
		}
		cout << endl;
	}
	
	
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		memset(L, 0, sizeof(L));
		memset(board, 0, sizeof(board));
		input();

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}