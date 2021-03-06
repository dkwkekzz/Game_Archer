#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321, MAX_V = 10;
int V;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int networkFlow(int source, int sink){
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	//0. 증가 경로를 찾으며 없을 때까지 반복
	while (true){
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		//1. 증가 경로 찾기
		while (!q.empty() && parent[sink] == -1){
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++)
			if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1){
				q.push(there);
				parent[there] = here;
			}
		}
		//5. 더 이상의 경로가 없으면 중단
		if (parent[sink] == -1) break;
		//2. 흘릴 수 있는 최대 용량(유량) 구하기
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]){
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		//3. 계산한 유량으로 남은 용량 갱신하기
		for (int p = sink; p != source; p = parent[p]){
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

int main(){

}