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
const int MAX_NM = 20 + 1, INF = 987654321;
int t, n, m;
string name[MAX_NM];
vector<string> food[MAX_NM];
vector<int> like[MAX_NM];
int cache[1 << MAX_NM][MAX_NM];

int cooking(int isDone, int who){
	if (who == n) return 0;

	int &ret = cache[isDone][who];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = 0; i < like[who].size(); i++){
		int thisCook = like[who][i];
		if (isDone & (1 << thisCook)) ret = min(ret, cooking(isDone, who + 1));
		else ret = min(ret, 1 + cooking(isDone | (1 << thisCook), who + 1));
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	
	cin.sync_with_stdio(false);
	cin >> t;
	for (int tc = 0; tc < t; tc++){
		memset(cache, -1, sizeof(cache));
		cin >> n >> m;
		for (int i = 0; i < n; i++) cin >> name[i];
		for (int i = 0; i < n; i++) like[i].clear();
		for (int i = 0; i < m; i++){
			int counter; cin >> counter;
			food[i] = vector<string>(counter);
			for (int j = 0; j < counter; j++){
				cin >> food[i][j];
				for (int k = 0; k < n; k++)
					if (food[i][j] == name[k]) 
						like[k].push_back(i);
			}
		}
		cout << cooking(0, 0) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}