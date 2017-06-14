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

const int INF = 987654321, MAX_N = 1001, MAX_W = 1002;

int n, w;
pair<int, int> W[MAX_W];
int C[MAX_W][MAX_W];

int calcDist(const pair<int, int>& a, const pair<int, int>& b){
	return abs(a.first - b.first) + abs(a.second - b.second);
}

void solve(){
	memset(C, -1, sizeof(C));
	C[1][0] = 0;
	for (int i = 1; i < w + 1; i++){
		for (int j = 0; j < w + 1; j++){
			if (C[i][j] != -1){
				C[i + 1][j] = C[i][j] + calcDist(W[i + 1], W[i]);
				C[i][i + 1] = C[i][j] + calcDist(W[i + 1], W[j]);
			}
			if (C[j][i] != -1){
				C[j][i + 1] = C[j][i] + calcDist(W[i + 1], W[i]);
				C[i + 1][i] = C[j][i] + calcDist(W[i + 1], W[j]);
			}
		}
	}

	int first, second, minValue = INF;
	for (int j = 0; j < w + 1; j++){
		if (C[w + 1][j] != -1 && C[w + 1][j] < minValue){
			minValue = C[w + 1][j];
			first = w + 1, second = j;
		}
		if (C[j][w + 1] != -1 && C[j][w + 1] < minValue){
			minValue = C[j][w + 1];
			first = j, second = w + 1;
		}
	}
	cout << minValue << endl;

	vector<int> ret;
	for (int i = w + 1; i >= 2; i--){
		if (first == i){
			ret.push_back(1);
			if (second != i - 1) first--;
			else first -= 2;
		}
		else if (second == i){
			ret.push_back(2);
			if (first != i - 1) second--;
			else second -= 2;
		}
	}
	for (int i = 0; i < ret.size(); i++) cout << ret[i] << endl;
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin >> n >> w;
	W[0] = make_pair(1, 1), W[1] = make_pair(n, n);
	for (int i = 2; i <= w + 1; i++) {
		int y, x; cin >> y >> x;
		W[i] = make_pair(y, x);
	}
	solve();

	return 0;
}