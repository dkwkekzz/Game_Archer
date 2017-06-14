#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;

int tc, n; 
string words[105];
vector<string> graph[26][26];
//���� ��� ǥ��
vector<vector<int> > adj;
//������ �������� ã�� ���� �ʿ�
vector<int> indegree, outdegree;

void getEulerCircuit(int here, vector<int>& circuit){
	for (int there = 0; there < adj.size(); there++){
		while (adj[here][there] > 0){
			adj[here][there]--;
			adj[there][here]--;
			getEulerCircuit(there, circuit);
		}
	}
	circuit.push_back(here);
}
//Ʈ�������� ��Ŷ���� �Ǵ��ϰ� �׿� �´� ��θ� ��ȯ
vector<int> getEulerCircuitOrTrail(){
	vector<int> circuit;
	for (int i = 0; i < 26; i++){
		if (indegree[i] == outdegree[i] + 1){
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	for (int i = 0; i < 26; i++){
		if (outdegree[i]){
			getEulerCircuit(i, circuit);
			return circuit;
		}
	}
	return circuit;
}
//��Ŷ�̳� Ʈ������ ���� ����
bool checkEuler(){
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++){
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}
	//Ʈ����(������ ���� �ϳ���) || ��Ŷ(��� ¦��)
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> tc;
	while (tc--){
		cin >> n;
		adj = vector<vector<int> >(26, vector<int>(26, 0));
		indegree = outdegree = vector<int>(26, 0);
		for (int i = 0; i < n; i++) {
			cin >> words[i];
			int begin = words[i][0] - 'a';
			int end = words[i][words[i].size() - 1] - 'a';
			graph[begin][end].push_back(words[i]);
			adj[begin][end]++;
			outdegree[begin]++;
			indegree[end]++;
		}
	}
	string ret;
	if (!checkEuler()) ret = "IMPOSSIBLE";
	else{
		vector<int> circuit = getEulerCircuitOrTrail();
		if (circuit.size() != n) ret = "IMPOSSIBLE";
		else{
			reverse(circuit.begin(), circuit.end());
			for (int i = 1; i < circuit.size(); i++){
				int a = circuit[i - 1], b = circuit[i];
				if (ret.size()) ret += " ";
				ret += graph[a][b].back();
				graph[a][b].pop_back();
			}
		}
	}
	cout << ret << endl;

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}
