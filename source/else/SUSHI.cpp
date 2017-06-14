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

const int MAX_N = 20, MAX_M = 10000000, MAX_P = 201;
int n, m;
int price[MAX_N], preference[MAX_N];
int C[MAX_P];

void init(){
	memset(C, 0, sizeof(C));
}

void input(){
	cin >> n >> m;
	m /= 100;
	for (int i = 0; i < n; i++){
		cin >> price[i] >> preference[i];
		price[i] /= 100;
	}
}

int solve(){
	int ret = 0;
	for (int i = 0; i <= m; i++){
		int cand = 0;
		for (int j = 0; j < n; j++){
			int p = price[j], pre = preference[j];
			if (i >= p){
				cand = max(cand, C[(i - p) % MAX_P] + pre);
			}
		}
		C[i%MAX_P] = cand;
		ret = max(ret, cand);
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		init(); input();

		cout << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}
