#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;

int tc, n;
vector<vector<int> > adj;
//서로 겹치면 거짓, 안 겹치면 참을 반환한다.
inline bool disjoint(const pair<int, int>& a, const pair<int, int>& b){
	//교차되는 양 끝점끼리 관계를 파악한다.
	return a.second <= b.first || b.second <= a.first;
}

void makeGraph(const vector<pair<int, int> >& meetings){
	int m = meetings.size();
	//각각의 회의에 대해 열릴 경우와 그것이 열리지 않을 경우
	//2가지가 있으므로 총 4*n입니다.  
	adj.clear(); adj.resize(2 * m);
	//각 팀은 i, j(i+1)입니다. 각 팀에 대해(+=2) 연결 관계를 추가합니다.
	for (int i = 0; i < m; i += 2){
		//i는 주간 회의, j는 월간 회의입니다.
		int j = i + 1; 
		//2*i+1(주간 회의가 열리지 않음) -> 2*j(월간 회의 열림)
		adj[2 * i + 1].push_back(2 * j);
		adj[2 * j + 1].push_back(2 * i);
	}
	//서로 간의 회의실 사용 여부 관계를 추가합니다.
	for (int i = 0; i < m; i++){
		for (int j = 0; j < i; j++){
			//i, j가 서로 겹쳐지면
			if (!disjoint(meetings[i], meetings[j])){
				//i가 열리면 j는 닫혀야 한다.
				//i열림(2*i) -> j닫힘(2*j+1)
				adj[2 * i].push_back(2 * j + 1);
				adj[2 * j].push_back(2 * i + 1);
			}
		}
	}
}

vector<int> sccId;
vector<int> discovered;
stack<int> st;
int sccCounter, vertexCounter;

int scc(int here){
	int ret = discovered[here] = vertexCounter++;
	st.push(here);
	for (int i = 0; i < adj[here].size(); i++){
		int there = adj[here][i];
		if (discovered[there] == -1) ret = min(ret, scc(there));
		else if (sccId[there] == -1) ret = min(ret, discovered[there]);
	}
	if (ret == discovered[here]){
		while (true){
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if (t == here) break;
		}
		sccCounter++;
	}
	return ret;
}

vector<int> tarjanSCC(){
	sccId = discovered = vector<int>(adj.size(), -1);
	sccCounter = vertexCounter = 0;
	for (int i = 0; i < adj.size(); i++) if (discovered[i] == -1) scc(i);
	return sccId;
}

vector<int> solve(){
	int n = adj.size();
	//SCC를 이용하여 DAG를 만든다.
	//SCC 번호를 담는 배열
	vector<int> labels = tarjanSCC();
	//각 SCC노드 안에(사이클 안에) i와 !i가 같이 들어있다면 불가능하다. 
	for (int i = 0; i < n; i+=2){
		if (labels[i] == labels[i + 1]) return vector<int>();
	}
	//이제 모든 회의가 진행될 수 있으므로 결과를 찾는다.
	vector<int> ret(n, -1);
	//각 SCC노드를 SCC번호대로 정렬하면 위상정렬된다.
	vector<pair<int, int> > order;
	for (int i = 0; i < n; i++){
		order.push_back(make_pair(-labels[i], i));
	}
	sort(order.begin(), order.end());
	//위상정렬한 순서대로 각 정점들에 참or거짓 값을 부여합니다. 
	//곧, A와 !A중 먼저 방문한 번호의 값을 부여합니다.
	for (int i = 0; i < n; i++){
		//vertex = i의 SCC번호를 가진 회의 번호
		int vertex = order[i].second; 
		//회의 번호: 회의 엶과 닫힘을 동시에 품는다.
		int variable = vertex / 2; 
		//해당 회의가 A이면 1, !A이면 0
		int isTrue = (vertex % 2 == 0); 
		//i, i+1(!i)중 먼저 나온 회의가 참이 됩니다.
		if (ret[variable] != -1) continue;
		//결국, A가 먼저 나오면 거짓, !A가 먼저 나오면 참
		ret[variable] = !isTrue;
	}
	return ret;
}

void printAnswer(const vector<pair<int, int> >& meetings, const vector<int>& ret){
	int n = ret.size();
	if (n == 0) cout << "IMPOSSIBLE" << endl;
	else{
		cout << "POSSIBLE" << endl;
		for (int i = 0; i < n/2; i++){
			if (ret[i] <= 0) continue;
			cout << meetings[i].first << " " << meetings[i].second << endl;
		}
	}
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> tc;
	while (tc--){
		cin >> n;
		vector<pair<int, int> > meetings(2*n);
		for (int i = 0; i < n; i++){
			cin >> meetings[2 * i].first >> meetings[2 * i].second
				>> meetings[2 * i + 1].first >> meetings[2 * i + 1].second;
		}
		makeGraph(meetings);
		printAnswer(meetings, solve());
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}