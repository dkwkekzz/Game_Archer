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
//���� ��ġ�� ����, �� ��ġ�� ���� ��ȯ�Ѵ�.
inline bool disjoint(const pair<int, int>& a, const pair<int, int>& b){
	//�����Ǵ� �� �������� ���踦 �ľ��Ѵ�.
	return a.second <= b.first || b.second <= a.first;
}

void makeGraph(const vector<pair<int, int> >& meetings){
	int m = meetings.size();
	//������ ȸ�ǿ� ���� ���� ���� �װ��� ������ ���� ���
	//2������ �����Ƿ� �� 4*n�Դϴ�.  
	adj.clear(); adj.resize(2 * m);
	//�� ���� i, j(i+1)�Դϴ�. �� ���� ����(+=2) ���� ���踦 �߰��մϴ�.
	for (int i = 0; i < m; i += 2){
		//i�� �ְ� ȸ��, j�� ���� ȸ���Դϴ�.
		int j = i + 1; 
		//2*i+1(�ְ� ȸ�ǰ� ������ ����) -> 2*j(���� ȸ�� ����)
		adj[2 * i + 1].push_back(2 * j);
		adj[2 * j + 1].push_back(2 * i);
	}
	//���� ���� ȸ�ǽ� ��� ���� ���踦 �߰��մϴ�.
	for (int i = 0; i < m; i++){
		for (int j = 0; j < i; j++){
			//i, j�� ���� ��������
			if (!disjoint(meetings[i], meetings[j])){
				//i�� ������ j�� ������ �Ѵ�.
				//i����(2*i) -> j����(2*j+1)
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
	//SCC�� �̿��Ͽ� DAG�� �����.
	//SCC ��ȣ�� ��� �迭
	vector<int> labels = tarjanSCC();
	//�� SCC��� �ȿ�(����Ŭ �ȿ�) i�� !i�� ���� ����ִٸ� �Ұ����ϴ�. 
	for (int i = 0; i < n; i+=2){
		if (labels[i] == labels[i + 1]) return vector<int>();
	}
	//���� ��� ȸ�ǰ� ����� �� �����Ƿ� ����� ã�´�.
	vector<int> ret(n, -1);
	//�� SCC��带 SCC��ȣ��� �����ϸ� �������ĵȴ�.
	vector<pair<int, int> > order;
	for (int i = 0; i < n; i++){
		order.push_back(make_pair(-labels[i], i));
	}
	sort(order.begin(), order.end());
	//���������� ������� �� �����鿡 ��or���� ���� �ο��մϴ�. 
	//��, A�� !A�� ���� �湮�� ��ȣ�� ���� �ο��մϴ�.
	for (int i = 0; i < n; i++){
		//vertex = i�� SCC��ȣ�� ���� ȸ�� ��ȣ
		int vertex = order[i].second; 
		//ȸ�� ��ȣ: ȸ�� ���� ������ ���ÿ� ǰ�´�.
		int variable = vertex / 2; 
		//�ش� ȸ�ǰ� A�̸� 1, !A�̸� 0
		int isTrue = (vertex % 2 == 0); 
		//i, i+1(!i)�� ���� ���� ȸ�ǰ� ���� �˴ϴ�.
		if (ret[variable] != -1) continue;
		//�ᱹ, A�� ���� ������ ����, !A�� ���� ������ ��
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

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}