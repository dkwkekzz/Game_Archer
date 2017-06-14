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

int n;
string s;

struct Comparator{
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t){}
	bool operator()(int i, int j){
		if (group[i] != group[j]) return group[i] < group[j];
		return group[i + t] < group[j + t];
	}
};

vector<int> getSuffixArray(){
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	while (t < n){
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		t *= 2;
		if (t >= n) break;
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (size_t i = 1; i < n; i++){
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		}
		group = newGroup;
	}
	return perm;
}

vector<int> makeLCP(const vector<int>& sa) {
	vector<int> rank(n), lcp(n);
	int i, j;
	int k = 0;
	for (i = 0; i < n; i++) rank[sa[i]] = i;
	for (i = 0; i < n; lcp[rank[i++]] = k) {
		for ((k ? k-- : 0), j = (rank[i] ? sa[rank[i] - 1] : n); i + k < n && j + k < n && s[i + k] == s[j + k]; k++);
	}
	return lcp;
}

int solve(){
	vector<int> sa(getSuffixArray());
	vector<int> lcp(makeLCP(sa));
	
	return *max_element(lcp.begin(), lcp.end());
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin >> n >> s;
	cout << solve() << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}