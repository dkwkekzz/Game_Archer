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

const int MAX_K = 100000;
int n, m, k;
vector<pair<int, int> > adj[MAX_K];
int C[MAX_K];

void init(){
	for (int i = 0; i < MAX_K; i++) adj[i].clear();
	memset(C, 0, sizeof(C));
}

void input(){
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++){
		int start, end, score;
		cin >> start >> end >> score;
		if (end <= start) continue;
		else adj[start].push_back(make_pair(end, score));
	}
}

int solve(){
	for (int i = n; i >= 1; i--){
		int here = i;
		for (int j = 0; j < adj[here].size(); j++){
			int there = adj[i][j].first, cost = adj[i][j].second;
			C[here] = max(C[here], C[there] + cost);
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	init(); input();
	cout << solve() << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}