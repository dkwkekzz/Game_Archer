#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int EMPTY = -987654321;
int n;
int board[50], cashe[50][50];

int select(int left, int right) {
	if (left > right) return 0;

	int &ret = cashe[left][right];
	if (ret != EMPTY) return ret;

	ret = max(board[right] - select(left, right - 1), board[left] - select(left + 1, right));
	if (right - left + 1 >= 2) {
		ret = max(ret, -select(left, right - 2));
		ret = max(ret, -select(left + 2, right));
	}
	
	return ret;
}

int main() {
	memset(cashe, EMPTY, sizeof(cashe));
	cin >> n;
	for (int i = 0; i < n; i++) cin >> board[i];

	cout << select(0, n - 1) << endl;
}