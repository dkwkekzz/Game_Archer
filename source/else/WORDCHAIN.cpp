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
//인접 행렬 표현
vector<vector<int> > adj;
//차수는 시작점을 찾기 위해 필요
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
//트레일인지 서킷인지 판단하고 그에 맞는 경로를 반환
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
//서킷이나 트레일의 존재 여부
bool checkEuler(){
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++){
		int delta = outdegree[i] - indegree[i];
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}
	//트레일(시작점 끝점 하나씩) || 서킷(모두 짝수)
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

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}
