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
typedef long long int64;
const int INF = 987654321, MAX_N = 20011, MAX_E = 100011;
int n, e;
vector<pair<int, int> > adj[MAX_N];
int V[MAX_N], cache[MAX_N], parent[MAX_N];
int C[MAX_N];

int maxIndex = 0;

void input(){
	scanf_s("%d %d", &n, &e);
	for (int i = 1; i <= n; i++) scanf_s("%d", &V[i]);
	for (int i = 0; i < e; i++) {
		int a, b, c; scanf_s("%d %d %d", &a, &b, &c);
		adj[a].push_back(make_pair(b, c));
	}
}
//재귀적으로 작동합니다.
int dfs(int here){
	int &res = cache[here];
	if (res != -1) return res;

	res = 0;
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i].first, cost = adj[here][i].second;
		int cand = dfs(there) - cost;
		if (res < cand) {
			res = cand;
			parent[here] = there;
		}
	}
	res += V[here];

	return res;
}
//반복적으로 작동합니다.
int solve(){
	for (int i = n; i >= 1; i--){
		int here = i;
		for (int j = 0; j < adj[here].size(); j++) {
			int there = adj[here][j].first, cost = adj[here][j].second;
			int cand = C[there] - cost;
			if (C[here] < cand){
				C[here] = cand;
				parent[here] = there;
			}
		}
		C[here] += V[here];
	}

	return C[1];
}

void findRoute(){
	vector<int> ret;
	int index = 1;
	while (index != -1){
		ret.push_back(index);
		index = parent[index];
	}
	int size = ret.size();
	cout << size << endl;
	for (int i = 0; i < size; i++) cout << ret[i] << " ";
	cout << endl;
}

void findRoute2(){
	vector<int> ret;
	int index = maxIndex;
	while (index != -1){
		ret.push_back(index);
		index = parent[index];
	}
	int size = ret.size();
	cout << size << endl;
	for (int i = 0; i < size; i++) {
		cout << ret.back() << " ";
		ret.pop_back();
	}
	cout << endl;
}

int main(int argc, char** argv) {
	FILE *stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		memset(V, 0, sizeof(V));
		memset(C, 0, sizeof(C));
		memset(cache, -1, sizeof(cache));
		memset(parent, -1, sizeof(parent));
		for (int i = 0; i < MAX_N; i++) adj[i].clear();

		input();

		//cout << dfs(1) << " ";
		cout << solve() << " ";
		findRoute();
	}

	return 0;
}