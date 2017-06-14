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

const int INF = 987654321;

int m, n, k;
int board[102][102];
int cache[102][102][10];

void input(){
	cin >> m >> n >> k;
	for (int y = 0; y < n + 1; y++){
		for (int x = 0; x < m + 1; x++){
			cin >> board[y][x];
		}
	}
}

int solve(int y, int x, int w){
	if (y > n || x > m) return INF;

	int &ret = cache[y][x][w];
	if (ret != -1) return ret;

	int altitude = board[y][x];
	if (altitude < 0 && w < 10) w++;

	if (y == n && x == m && w >= k) return ret = 0;

	return ret = min(abs(abs(altitude) - abs(board[y + 1][x])) + solve(y + 1, x, w), 
		abs(abs(altitude) - abs(board[y][x + 1])) + solve(y, x + 1, w));
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		memset(board, -1, sizeof(board));
		memset(cache, -1, sizeof(cache));
		input();

		cout << "Case #" << test_case << "\n" << solve(0, 0, 0) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}