#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;

const int MOD = 1000000007, N = 5000;
const int const_exp[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
int n, minCounter = N, parent[N];
vector<vector<int> > adj;

bool check(const int k){
	for (int i = 0; i < 12; i++) if (const_exp[i] == k) return true;
	return false;
}

int dfs(int here, int counter, int cut){
	if (minCounter < counter) return 0;
	if (counter > 0 && here == 1) {
		minCounter = min(minCounter, counter);
		return 1;
	}
	
	int ret = 0;
	for (int i = 0; i < adj[here].size(); i++){
		int there = adj[here][i];
		if (!parent[there]) parent[there] = here;
		if (parent[here] == there) continue;
		ret += dfs(there, counter + 1, cut);
		if (check(counter)) ret += dfs(there, 1, cut + 1);
	}
	return ret += dfs(parent[here], counter, cut);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> n;
	adj = vector<vector<int> >(n + 1, vector<int>());
	for (int i = 0; i < n - 1; i++){
		int u, v; cin >> u >> v;
		adj[u].push_back(v); adj[v].push_back(u);
	}
	dfs(1, 1, 0);

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}