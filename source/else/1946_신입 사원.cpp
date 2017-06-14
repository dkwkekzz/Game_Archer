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

int t, n;
vector<pair<int, int> > score;

int solve(){
	sort(score.begin(), score.end());
	int prior = score[0].second, ret = 1;
	for (int i = 1; i < n; i++){
		int value = score[i].second;
		if (value < prior){
			ret++;
			prior = value;
		}
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	scanf_s("%d", &t);
	for (int tc = 0; tc < t; tc++){
		scanf_s("%d", &n);
		score = vector<pair<int, int> >(n, make_pair(0, 0));
		for (int i = 0; i < n; i++){
			scanf_s("%d %d", &score[i].first, &score[i].second);
		}
		sort(score.begin(), score.end());
		cout << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}