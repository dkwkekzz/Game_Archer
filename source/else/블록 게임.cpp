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
const int MAX_NM = 100 * 2 + 5;
int n, m;
double k;
char board[MAX_NM][MAX_NM];

int counter = 0;

void init(){

}

void input(){
	cin >> m >> n >> k;
	for (int y = 0; y <= 2*n; y++)
		for (int x = 0; x <= 2*m; x++)
			cin >> board[y][x];
}

void preCalc(){

}

void destroyBlock(int y, int x){
	board[y][x] = 'O';
	if (board[y + 1][x] == '.') destroyBlock(y + 1, x);
	if (board[y][x + 1] == '.') destroyBlock(y, x + 1);
	if (board[y - 1][x] == '.') destroyBlock(y - 1, x);
	if (board[y][x - 1] == '.') destroyBlock(y, x - 1);
}

int shot(int y, int x, int dirY, int dirX){
	if (y < 0) return 0;
	if (x == 0 || x == 2 * m) dirX *= -1;
	if (y == 2 * n) dirY *= -1;

	if (board[y + dirY][x] == 'B') {
		destroyBlock(y + dirY, x); counter++;
	}
	if (board[y][x + dirX] == 'B') {
		destroyBlock(y, x + dirX); counter++;
	}
	if (board[y + dirY][x + dirX] == 'B') {
		destroyBlock(y + dirY, x + dirX); counter++;
	}

	return shot(y + dirY, x + dirX, dirY, dirX);
}

int solve(){
	int ret = 0;

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	init(); input(); preCalc(); shot(0, 2 * k, 1, -1);
	cout << counter << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}