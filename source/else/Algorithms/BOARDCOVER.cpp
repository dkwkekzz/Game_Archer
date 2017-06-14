#include <iostream>
#include <string>
#include <vector>
using namespace std;

int c, h, w;
int board[50][20];
/*int block[4][2][2] = {
	{{-1, 0}, {0, -1}},
	{{-1, 0}, {0, 1}},
	{{1, 0}, {0, -1}},
	{{1, 0}, {0, 1}}
};

int cover(int y, int x, int rest) {
	if (rest % 3 != 0) return 0;
	if (rest == 0) return 1;
	if (x == w) return cover(y + 1, 0, rest);
	if (y == h) return 0;
	if (y >= 2) {
		for (int i = 0; i < w; i++) 
			if (board[y - 2][i]) return 0;
	}

	int ret = 0;
	if (!board[y][x]) return cover(y, x + 1, rest);
	else {
		board[y][x] = false;
		for (int i = 0; i < 4; i++) {
			if (board[y + block[i][0][0]][x + block[i][0][1]] && board[y + block[i][1][0]][x + block[i][1][1]]) {
				board[y + block[i][0][0]][x + block[i][0][1]] = board[y + block[i][1][0]][x + block[i][1][1]] = false;
				ret += cover(y, x + 1, rest - 3);
				board[y + block[i][0][0]][x + block[i][0][1]] = board[y + block[i][1][0]][x + block[i][1][1]] = true;
			}
		}
		board[y][x] = true;
		ret += cover(y, x + 1, rest);
	}

	return ret;
}*/

const int coverType[4][3][2] = {
	{ { 0, 0 },{ 1, 0 },{ 0, 1 } },
	{ { 0, 0 },{ 0, 1 },{ 1, 1 } },
	{ { 0, 0 },{ 1, 0 },{ 1, 1 } },
	{ { 0, 0 },{ 1, 0 },{ 1, -1 } }
};

bool set(vector<vector<int> > &board, int y, int x, int type, int delta) { //덮을 수 있는지 없는지 확인한다.
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= h || nx < 0 || nx >= w) ok = false;
		else if ((board[ny][nx] += delta) > 1) ok = false; //delta가 1이면 덮고 아니면 덮지 않는다.
	}
	return ok;
}

int cover(vector<vector<int> > &board) {
	//빈칸이 있는지 순회한다.
	int y = -1, int x = -1;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			y = i;
			x = j;
			break;
		}
		if (y != -1) break;
	}
	//기저사례
	if (y == -1) return 1;
	//블록 모양별로 빈 칸에 들어가는지 확인한다.
	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1)) {
			ret += cover(board);
		}
		set(board, y, x, type, -1);
	}
	return ret;
}

int main() {
	string line;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int rest = 0;
		cin >> h >> w;
		for (int j = 0; j < h; j++) {
			cin >> line;
			for (int k = 0; k < w; k++) {
				if (line[k] == '.') {
					board[j][k] = 1;
					rest++;
				}
				else board[j][k] = 0;
			}
		}
		//cout << cover(0, 0, rest) << endl;
	}
}