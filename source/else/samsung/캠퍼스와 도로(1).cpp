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

const int MAX_N = 1001, INF = 987654321;

int n, m;

vector<pair<int, int> >adj[MAX_N];

struct pass{
	int here;
	vector<int> sameDist;
};

vector<pass> dijkstra(int src){
	vector<pass> parent(n + 1);
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
				parent[there].here = here;
				parent[there].sameDist.clear();
				parent[there].sameDist.push_back(here);
			}
			if (dist[there] == nextDist){
				parent[there].sameDist.push_back(here);
			}
		}
	}

	return parent;
}

void input(){
	cin >> n >> m;
	for (int i = 1; i < n + 1; i++){
		adj[i] = vector<pair<int, int> >();
	}
	for (int i = 0; i < m; i++){
		int here, there, distance;
		cin >> here >> there >> distance;
		adj[here].push_back(make_pair(there, distance));
		adj[there].push_back(make_pair(here, distance));
	}
}

vector<int> solve(){
	vector<bool> visited(n + 1, 0);

	for (int i = 1; i < n + 1; i++){
		vector<pass> parent = dijkstra(i);

		for (int j = 1; j < n + 1; j++) {
			pass p(parent[j]);
			for (int k = 0; k < p.sameDist.size(); k++){
				int here = p.sameDist[k];
				if (here > 0 && i != here) visited[here] = 1;
			}
		}
	}

	vector<int> ret;
	for (int i = 1; i < n + 1; i++) if (!visited[i]) ret.push_back(i);
	
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		vector<int> ret = solve();
		cout << "Case #" << test_case << "\n";
		cout << ret.size() << " ";
		for (int i = 0; i < ret.size(); i++) cout << ret[i] << " ";
		cout << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}