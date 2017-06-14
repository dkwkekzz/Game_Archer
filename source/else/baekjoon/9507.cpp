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
const int INF = 987654321, MAX_N = 68;
int n;
uint64 C[MAX_N];

void input(){
	cin >> n;
}

int pre_solve(){
	C[0] = C[1] = 1; C[2] = 2; C[3] = 4;
	for (int i = 4; i <= 67; i++){
		C[i] = C[i - 1] + C[i - 2] + C[i - 3] + C[i - 4];
	}

	return 0;
}

uint64 solve(){
	return C[n];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	pre_solve();
	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << solve() << endl;
	}

	return 0;
}