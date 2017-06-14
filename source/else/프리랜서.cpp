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

const int MAX_N = 10001;
int n;
int P[MAX_N], Q[MAX_N];
int C[MAX_N][2];

void init(){
	memset(P, 0, sizeof(P));
	memset(Q, 0, sizeof(Q));
	memset(C, 0, sizeof(C));
}

void input(){
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> P[i];
	for (int i = 1; i <= n; i++) cin >> Q[i];
}

void preCalc(){

}

int solve(){
	C[1][0] = P[1]; C[1][1] = Q[1];
	for (int week = 2; week <= n; week++){
		C[week][0] = max(C[week - 1][0], C[week - 1][1]) + P[week];
		C[week][1] = max(C[week - 2][0], C[week - 2][1]) + Q[week];
	}

	return max(C[n][0], C[n][1]);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		init(); input(); preCalc();

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}