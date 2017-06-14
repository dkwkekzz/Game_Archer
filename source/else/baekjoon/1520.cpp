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
int m, n;
int cache[501][501];

void input(vector<vector<int> >& board){
	cin >> m >> n;
	board = vector<vector<int> >(m + 3, vector<int>(n + 3, -1));
	for (int y = 1; y <= m; y++){
		for (int x = 1; x <= n; x++){
			cin >> board[y][x];
		}
	}
}

int solve(const vector<vector<int> >& board, int y, int x){
	if (y == m && x == n) return 1;
	if (y > m || x > n || y < 1 || x < 1) return 0;

	int &ret = cache[y][x];
	if (ret != -1) return ret;

	ret = 0;
	int here = board[y][x];
	if (board[y - 1][x] < here) ret += solve(board, y - 1, x);
	if (board[y][x - 1] < here) ret += solve(board, y, x - 1);
	if (board[y + 1][x] < here) ret += solve(board, y + 1, x);
	if (board[y][x + 1] < here) ret += solve(board, y, x + 1);

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	memset(cache, -1, sizeof(cache));
	vector<vector<int> >board;
	input(board);
	cout << solve(board, 1, 1) << endl;

	return 0;
}