#include <iostream>
#include <string>
using namespace std;

const string board[5] = {
	"URLPM",
	"XPRET",
	"GIAET",
	"XTNZY",
	"XOQRS"
};

const int searchChar[8][2] = {
	{-1, -1},
	{-1, 0},
	{-1, 1},
	{0, -1},
	{0, 1},
	{1, -1},
	{1, 0},
	{1, 1}
};

bool hasWord(int y, int x, string &Word) {
	if (y < 0 || x < 0) return false;
	if (board[y][x] != Word[0]) return false;
	if (Word.size() == 1) return true;
	for (int i = 0; i < 8; i++) {
		if (hasWord(y + searchChar[i][0], x + searchChar[i][1], Word.substr(1))) return true;
	}
	return false;
}

void main() {
	string Word;
	cin >> Word;
	if (hasWord(1, 1, Word)) cout << "true" << endl;
}