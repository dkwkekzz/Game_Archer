#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321, MAX_V = 10;
int V;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int networkFlow(int source, int sink){
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	//0. ���� ��θ� ã���� ���� ������ �ݺ�
	while (true){
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		//1. ���� ��� ã��
		while (!q.empty() && parent[sink] == -1){
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++)
			if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1){
				q.push(there);
				parent[there] = here;
			}
		}
		//5. �� �̻��� ��ΰ� ������ �ߴ�
		if (parent[sink] == -1) break;
		//2. �긱 �� �ִ� �ִ� �뷮(����) ���ϱ�
		int amount = INF;
		for (int p = sink; p != source; p = parent[p]){
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);
		}
		//3. ����� �������� ���� �뷮 �����ϱ�
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