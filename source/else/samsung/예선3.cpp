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

int k, l, n, m;

vector<vector<int> > adj;
vector<int> discovered;
vector<bool> isCutVertex;
int counter = 0;

int findCutVertex(int here, bool isRoot){
	discovered[here] = counter++;
	int ret = discovered[here];
	int children = 0;
	for (int i = 1; i < adj[here].size(); i++){
		int there = adj[here][i];
		if (discovered[there] == -1){
			++children;
			int subtree = findCutVertex(there, false);
			if (!isRoot && subtree >= discovered[here])
				isCutVertex[here] = true;
			ret = min(ret, subtree);
		}
		else{
			ret = min(ret, discovered[there]);
		}
	}
	if (isRoot) isCutVertex[here] = (children >= 2);
	return ret;
}

struct robot{
	int n;
	int edge;
};

void input(){
	cin >> k >> l >> n >> m;
	adj = vector<vector<int> >(n + 1, vector<int>(n + 1, 0));
	for (int i = 0; i < m; i++){
		int here, there;
		cin >> here >> there;
		adj[here].push_back(there);
		adj[there].push_back(here);
	}
	discovered = vector<int>(n + 1, -1);
	isCutVertex = vector<bool>(n + 1, false);
	counter = 0;
}



int solve(){
	cout << "!" << endl;
	findCutVertex(1, true);

	for (int i = 0; i < isCutVertex.size(); i++) cout << isCutVertex[i] << " ";
	cout << endl;

	return 0;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}