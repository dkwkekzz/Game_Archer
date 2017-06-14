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

const int64 INF = 9876543210, MAX_N = 100001;
int n, m, k;
int K[MAX_N];
vector<pair<int64, int64> > adj[MAX_N];

void input(){
	memset(K, -1, sizeof(K));
	cin >> n >> m >> k;
	for (int i = 0; i < n + 1; i++){
		adj[i] = vector<pair<int64, int64> >();
	}
	for (int i = 0; i < m; i++){
		int here, there, distance;
		cin >> here >> there >> distance;
		adj[here].push_back(make_pair(there, distance));
		adj[there].push_back(make_pair(here, distance));
	}
	for (int i = 0; i < k; i++){
		cin >> K[i];
	}
}

vector<int64> dijkstra(vector<int64>& parent, int src){
	vector<int64> dist(n + 1, INF);
	dist[src] = 0;
	priority_queue<pair<int64, int64> > pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()){
		int64 cost = -pq.top().first;
		int64 here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); i++){
			int64 there = adj[here][i].first;
			int64 nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist){
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
				parent[there] = here;
			}
		}
	}

	return dist;
}

pair<int64, int64> solve(){
	int64 sumDist = 0, sumNum = 0;

	for (int i = 0; i < k; i++){
		adj[0].push_back(make_pair(K[i], 0));
		adj[K[i]].push_back(make_pair(0, 0));
	}
	vector<int64> parent(n + 1, 0);
	vector<int64> dist(dijkstra(parent, 0));
	for (int nearest = 0; nearest < dist.size(); nearest++){
		sumDist += dist[nearest];
	}
	for (int nearestBunker = 1; nearestBunker < n + 1; nearestBunker++){
		int v = nearestBunker;
		while (parent[v] != 0){
			v = parent[v];
		}
		sumNum += v;
	}

	return pair<int64, int64>(sumDist, sumNum);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		pair<int64, int64> s_p = solve();
		cout << "Case #" << test_case << "\n" << s_p.first << "\n" << s_p.second << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}