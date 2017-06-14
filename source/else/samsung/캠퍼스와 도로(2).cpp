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
const int INF = 987654321, MAX_N = 501, MAX_M = 5001;
int n, m;
vector<pair<int, int> > adj[MAX_N];
vector<int> university;

void input(){
	scanf_s("%d %d", &n, &m);
	for (int i = 0; i < MAX_N; i++) adj[i].clear();
	for (int i = 0; i < m; i++) {
		int here, there, dist;  scanf_s("%d %d %d", &here, &there, &dist);
		adj[here].push_back(make_pair(there, dist));
		adj[there].push_back(make_pair(here, dist));
	}
	university = vector<int>(n + 1, 0);
}

void dijkstra(int src){
	vector<int> parent(n + 1, src);
	vector<int> dist(n + 1, INF);
	vector<int> isDuplicate(n + 1, 0);
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
				isDuplicate[there] = 0;
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
				parent[there] = here;
			}
			else if (dist[there] == nextDist) isDuplicate[there]++;
		}
	}

	for (int i = 1; i <= n; i++){
		if (parent[i] != src && !isDuplicate[i]) {
			university[parent[i]] = 1;
		}
	}
}

void solve(){
	for (int i = 1; i <= n; i++) dijkstra(i);

	vector<int> ret;
	int counter = 0;
	for (int i = 0; i < university.size(); i++){
		if (university[i] > 0){
			counter++;
			ret.push_back(i);
		}
	}
	printf("%d ", counter);
	for (int i = 0; i < ret.size(); i++) printf("%d ", ret[i]);
	printf("\n");
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	//setbuf(stdout, NULL);

	int TC;
	scanf_s("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		printf("Case #%d\n", test_case);
		solve();
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}