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

const int MAX_N = 1000000000, MAX_SQRTN = 31624;

int b_cache[MAX_SQRTN][30];

void preCalc(){
	for (long long i = 2; i < MAX_SQRTN; i++){
		long long exp = 1;
		for (long long j = 1; j < 30; j++){
			exp *= i;
			if (exp > MAX_N * (i + 1)) {
				for (int k = j; k < 30; k++) b_cache[i][k] = -1;
				break;
			}
			b_cache[i][j] = (exp - 1) / (i - 1);
		}
	}
}

int solve(int n){
	int min_b = n + 1;
	for (int i = 2; i < MAX_SQRTN; i++){
		int j;
		for (j = 1; j < 30; j++){
			int b_c = b_cache[i][j];
			if (b_c > n || b_c == -1) break;
			if (n % b_c == 0 && (n / b_c) < i) min_b = min(min_b, i);
		}
		if (j == 2) break;
	}

	for (int i = sqrt(n); i >= 1; i--){
		if (n % i == 0) {
			int temp = n / i;
			if (temp > i) min_b = min(min_b, temp - 1); break;
		}
	}

	return min_b;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	/*int **b_cache = new int*[MAX_SQRTN];
	for (int i = 0; i < MAX_SQRTN; i++)
		b_cache[i] = new int[30];*/

	preCalc();

	int TC;
	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		int n;
		cin >> n;

		cout << "Case #" << test_case << "\n" << solve(n) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}