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
const int INF = 987654321, MAX_N = 100001;
int n;
int S[MAX_N];
vector<int> adj;
vector<int> visited;

int order;

void input(){
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> S[i];

	adj = vector<int>(n + 1, -1);
	for (int i = 1; i <= n; i++) adj[i] = S[i];
	visited = vector<int>(n + 1, 0);
	order = 1;
}

int solve(){
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int here = i;
		vector<int> path(n + 1, -1);
		while (!visited[here]){
			visited[here] = true;
			path[here] = order++;
			if (adj[here] != -1) here = adj[here];
			else break;
			if (path[here] != -1) ret += order - path[here];
		}
	}

	return n - ret;
}

int main(int argc, char** argv) {
	FILE *stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << solve() << endl;
	}

	return 0;
}