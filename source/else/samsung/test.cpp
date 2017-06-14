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

const int INF = 987654321, MAX_N = 1000;
int n, k, w;
vector<pair<int, int> > adj[MAX_N + 1];

vector<int> bellmanFord(int src){
	int V = n + 1;
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated;
	for (int iter = 0; iter < V; iter++){
		updated = false;
		for (int here = 0; here < V; here++){
			for (int i = 0; i < adj[here].size(); i++){
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost){
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}
		if (!updated) break;
	}
	if (updated) upper.clear();

	return upper;
}

/*vector<int> dijkstra(int src){
	vector<int> dist(n + 1, INF);
	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()){
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); i++){
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist){
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}

	return dist;
}*/

void input(){
	cin >> n >> k;
	vector<int> dist(n + 1);
	vector<bool> visited(n + 1, 0);
	for (int i = 1; i <= n; i++){
		cin >> dist[i];
	}
	for (int i = 0; i < n + 1; i++){
		adj[i] = vector<pair<int, int> >();
	}
	for (int i = 0; i < k; i++){
		int x, y; cin >> x >> y;
		adj[x].push_back(make_pair(y, -dist[y]));
		visited[y] = 1;
	}
	cin >> w;

	for (int i = 1; i <= n; i++){
		if (!visited[i]) adj[0].push_back(make_pair(i, -dist[i]));
	}
}

int solve(){
	vector<int> dist = bellmanFord(0);

	return -dist[w];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}