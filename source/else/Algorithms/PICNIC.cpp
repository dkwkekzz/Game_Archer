#include <iostream>
#include <vector>
using namespace std;

int t, n, m;
int Pair[10][10];

int getPair(vector<int> &Friend, int rest, int i) {
	int ret = 0;
	if (rest == 0) return 1;
	if (!Friend[i] && i < n) return getPair(Friend, rest, i + 1);
	if (i == n) return 0;
	for (int j = 0; j < n; j++) {
		if (Pair[i][j] && Friend[j]) {
			Friend[i] = 0;
			Friend[j] = 0;
			ret += getPair(Friend, rest - 2, i + 1);
			Friend[i] = 1;
			Friend[j] = 1;
		}
	}
	return ret;
}

int main() {
	vector<int> Friend;
	cin >> t;
	for (int ti = 0; ti < t; ti++){
		cin >> n;
		for (int i = 0; i < n; i++)
			Friend.push_back(1);
		cin >> m;
		for (int i = 0; i < m; i++) {
			int y, x;
			cin >> y >> x;
			Pair[y][x] = 1;
			Pair[x][y] = 1;
		}
		cout << getPair(Friend, n, 0) << endl;
		memset(Pair, 0, sizeof(Pair));
	}
	
}