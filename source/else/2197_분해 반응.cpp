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
const int INF = 987654321, MAX_N = 150 + 5;
int n, m;
vector<pair<int, int> > edge[MAX_N];
pair<int, int> c[MAX_N];

void makeCands(vector<bool>& newCands, const vector<bool>& cands, int node){
	for (int i = 0; i < edge[node].size(); i++){
		int value = edge[node][i].second;
		if (!newCands[value] && cands[value] && value != node){
			newCands[value] = true;
			int newNode = edge[node][i].first;
			makeCands(newCands, cands, newNode);
		}
	}
}

int check(const vector<bool>& cands){
	int ret = 1;
	for (int i = 0; i < cands.size(); i++) if (cands[i]) ret++;
	return ret;
}

int dc(vector<bool>& cands){
	int t = check(cands);
	if (t < m) return INF;
	if (t == m) return 0;

	int ret = INF;
	for (int i = 0; i < cands.size(); i++){
		if (cands[i]) {
			cands[i] = false;
			int index = i;
			int f = c[index].first, s = c[index].second;
			vector<bool> newCands1(n - 1, false), newCands2(n - 1, false);
			makeCands(newCands1, cands, f);
			makeCands(newCands2, cands, s);
			ret = min(ret, 1 + min(dc(newCands1), dc(newCands2)));
			cands[i] = true;
		}
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	scanf_s("%d %d", &n, &m);
	vector<bool> cands(n - 1, true);
	for (int i = 0; i < n - 1; i++) {
		//scanf_s("%d %d", &edge[i].first, &edge[i].second);
		int a, b; scanf_s("%d %d", &a, &b);
		edge[a].push_back(make_pair(b, i));
		edge[b].push_back(make_pair(a, i));
		c[i] = make_pair(a, b);
	}
	cout << dc(cands) << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}