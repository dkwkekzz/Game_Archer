#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int board = 0;
int cashe[1<<26];
int block3[4][2][2] = {
	{{0, 1}, {-1, 1}},
	{{0, 1}, {1, 1}},
	{{1, 0}, {1, 1}},
	{{1, 0}, {0, 1}},
};
int block2[2][2] = {
	{0, 1},
	{1, 0},
};	

int boardGame(int board, int rest, int turn){
	if(rest == 0 && turn % 2 == 0) return 0;
	else if (rest == 0) return 1;
	/*if(rest < 2 || turn % 2 == 1) return 1;
	else if(rest < 2) return 0;*/

	int &ret = cashe[board];
	if(ret != -1) return ret;

	ret = 1;
	int paramBoard = 0;
	for(int index = 0; index < 25; index++){
		if(((1<<index)&board) == 0){
			for(int i = 0; i < 4; i++){
				if(((1<<(index + block3[i][0][0] + block3[i][0][1] * 5))&board) == 0 
					&& ((1<<(index + block3[i][1][0] + block3[i][1][1] * 5))&board) == 0){
					paramBoard = ((board&(1<<index))
					&(1<<(index + block3[i][0][0] + block3[i][0][1] * 5)))
					&(1<<(index + block3[i][1][0] + block3[i][1][1] * 5));
					ret *= boardGame(paramBoard, rest - 3, turn + 1);
				}
				if(i >= 2) continue;
				else if(((1<<(index + block2[i][0] + block2[i][1] * 5))&board) == 0){
					paramBoard = (board&(1<<index))&(1<<(index + block2[i][0] + block2[i][1] * 5));
					ret *= boardGame(paramBoard, rest - 2, turn + 1);
				}
			}
		}
	}
	if(paramBoard == 0 && turn % 2 == 0) return 0;

	return ret;
}

int main(){
	memset(cashe, -1, sizeof(cashe));
	int rest = 25;
	for(int i = 0; i < 25; i++){
		char c;
		cin >> c;
		if(c == '#') {
			board |= (1<<i);
			rest--;
		}
	}

	if(boardGame(board, rest, 1) == 0) cout << "WINNING" << endl;
	else cout << "LOSING" << endl;
}

