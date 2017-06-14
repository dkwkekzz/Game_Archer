
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

int k;
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

vector<int> getSuffixArray(const string& s){
	int n = s.size();
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
		for (int i = 1; i < n; i++){
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		}
		group = newGroup;
	}
	return perm;
}

vector<int> makeLCP(const string& s, const vector<int>& sa) {
	int n = s.size();
	vector<int> rank(n), lcp(n);
	int i, j;
	int k = 0;
	for (i = 0; i < n; i++) rank[sa[i]] = i;
	for (i = 0; i < n; lcp[rank[i++]] = k) {
		for ((k ? k-- : 0), j = (rank[i] ? sa[rank[i] - 1] : n); i + k < n && j + k < n && s[i + k] == s[j + k]; k++);
	}
	return lcp;
}

int commonPrefix(const string& s, int i, int j){
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]){
		i++; j++; k++;
	}
	return k;
}

int countSubstrings(const string& s){
	vector<int> sa = getSuffixArray(s);
	vector<int> lcp = makeLCP(s, sa);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i + k < n; i++){
		ret = max(ret, commonPrefix(s, sa[i], sa[i + k - 1]));
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	int t; cin >> t;
	for (size_t i = 0; i < t; i++)
	{
		cin >> k >> s;
		cout << countSubstrings(s) << endl;
	}
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}