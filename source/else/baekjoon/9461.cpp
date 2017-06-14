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
const uint64 INF = 987654321, MAX_N = 110;
int n;
uint64 P[MAX_N];

void input(){
	cin >> n;
}

uint64 solve(){
	return P[n - 1];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	P[0] = P[1] = P[2] = 1;
	P[3] = P[4] = 2;
	for (int i = 5; i < MAX_N; i++){
		P[i] = P[i - 1] + P[i - 5];
	}

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << solve() << endl;
	}

	return 0;
}