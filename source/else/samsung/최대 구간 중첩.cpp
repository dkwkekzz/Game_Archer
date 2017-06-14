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
typedef unsigned long long uint64;

const int MAX_N = 10000000;

int n;

bool compare(pair<int, int> i, pair<int, int> j){
	return (i.first < j.first) || (i.first == j.first && i.second > j.second);
}

void input(vector<int>& section_end){
	cin >> n;
	vector<pair<int, int> > section;
	for (int i = 0; i < n; i++){
		int a, b; cin >> a >> b;
		section.push_back(make_pair(a, b));
	}
	sort(section.begin(), section.end(), compare);
	for (int i = 0; i < n; i++) {
		section_end.push_back(section[i].second);
	}
}

int solve(const vector<int>& section_end){
	vector<int> c;
	vector<int>::iterator up;
	for (int i = 0; i < n; i++){
		int curN = section_end[n - i - 1];
		if (c.empty() || c.back() <= curN) c.push_back(curN);
		else{
			up = upper_bound(c.begin(), c.end(), curN);
			c[up - c.begin()] = curN;
		}
	}

	return c.size();
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		vector<int> section_end;
		input(section_end);

		cout << "Case #" << test_case << "\n" << solve(section_end) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}