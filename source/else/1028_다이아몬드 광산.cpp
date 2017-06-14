#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;

const int MAX_N = 750;
int r, c;
string mine[MAX_N + 5];
int C[MAX_N + 5][MAX_N + 5][2][2];// 0: 위에서 아래로 올라가는 경우// 1: 아래에서 위로

int solve(){
	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++){
			if (mine[y - 1][x - 1] == '1'){
				C[y][x][0][0] = C[y - 1][x - 1][0][0] + 1;
				C[y][x][0][1] = C[y - 1][x + 1][0][1] + 1;
			}
		}
	}
	for (int y = r; y >= 1; y--) {
		for (int x = 1; x <= c; x++){
			if (mine[y - 1][x - 1] == '1'){
				C[y][x][1][0] = C[y + 1][x - 1][1][0] + 1;
				C[y][x][1][1] = C[y + 1][x + 1][1][1] + 1;
			}
		}
	}

	int ret = 0;
	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++){
			int value = min(C[y][x][1][0], C[y][x][1][1]);
			for (int i = value; i > 0; i--){
				if (y + (i * 2 - 2) <= r
					&& i <= min(C[y + (i * 2 - 2)][x][0][0], C[y + (i * 2 - 2)][x][0][1])){
					ret = max(ret, i);
					break;
				}
			}
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin >> r >> c;
	for (int y = 0; y < r; y++) cin >> mine[y];
	cout << solve() << endl;

	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++)
			cout << "(" << C[y][x][0][0] << "," << C[y][x][0][1] << ")";
		cout << endl;
	}
	cout << "=====================" << endl;
	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++)
			cout << "(" << C[y][x][1][0] << "," << C[y][x][1][1] << ")";
		cout << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}