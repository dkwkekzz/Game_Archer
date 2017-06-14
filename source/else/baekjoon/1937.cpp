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
const int INF = 987654321, MAX_N = 505;
int n;
int forest[MAX_N][MAX_N];
int cache[MAX_N][MAX_N];

void input(){
	cin >> n;
	for (int i = 1; i < n + 1; i++){
		for (int j = 1; j < n + 1; j++){
			cin >> forest[i][j];
		}
	}
}

int findForest(int y, int x){
	if (y > n || x > n || y < 1 || x < 1) return 0;

	int &ret = cache[y][x]; 
	if (ret != -1) return ret;
	ret = 0;
	int here = forest[y][x];
	if (here < forest[y + 1][x]) ret = max(ret, findForest(y + 1, x) + 1);
	if (here < forest[y - 1][x]) ret = max(ret, findForest(y - 1, x) + 1);
	if (here < forest[y][x + 1]) ret = max(ret, findForest(y, x + 1) + 1);
	if (here < forest[y][x - 1]) ret = max(ret, findForest(y, x - 1) + 1);

	return ret;
}

int solve(){
	int ret = 0;
	for (int i = 1; i < n + 1; i++){
		for (int j = 1; j < n + 1; j++){
			ret = max(ret, findForest(i, j) + 1);
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	memset(forest, -1, sizeof(forest));
	memset(cache, -1, sizeof(cache));
	input();

	cout << solve() << endl;

	return 0;
}