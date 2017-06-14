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

int ability[4];

void input(){
	for (int i = 0; i < 4; i++) cin >> ability[i];
	int temp;
	for (int i = 0; i < 4; i++) {
		cin >> temp;
		ability[i] += temp;
	}
}

int solve(){
	int ret = 0;
	if (ability[0] < 1) ret += 1;
	else ret += ability[0];
	if (ability[1] < 1) ret += 1 * 5;
	else ret += (ability[1] * 5);
	if (ability[2] < 0) ret += 0;
	else ret += (ability[2] * 2);
	ret += (ability[3] * 2);

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();
		
		cout << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}