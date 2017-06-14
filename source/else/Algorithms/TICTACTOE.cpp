#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bool isFinished(const vector<string> &board, char turn) {
	for (int y = 0; y < 3; y++)
		if (board[y] == string(turn, 3))
			return true;
	for (int x = 0; x < 3; x++)
		if (board[0][x] == board[1][x] == board[2][x] == turn)
			return true;
	if ((board[0][0] == board[1][1] == board[2][2] == turn) || (board[2][0] == board[1][1] == board[0][2] == turn))
		return true;
	return false;
}

int bijection(const vector<string> &board) {
	int ret = 0;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) {
			ret = ret * 3;
			if (board[y][x] == 'o') ret++;
			else if (board[y][x] == 'x') ret += 2;
		}
	return ret;
}

int cashe[19683];

int canWin(vector<string> &board, char turn) {
	if (isFinished(board, 'o' + 'x' - turn)) return -1;

	int &ret = cashe[bijection(board)];
	if (ret != -2) return ret;

	int minValue = 2;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++) 
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
	if (minValue == 2 || minValue == 0) return ret = 0;
	return ret = -minValue;
}