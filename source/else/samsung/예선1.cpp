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

int n;
int cache[1000000];

void input(){
	cin >> n;
}

int calc(int n){
	int count = 0;
	for (int i = 1; i < 1000000; i++){
		int temp = i;
		while (temp > 1){
			if (temp & 1){
				temp = temp * 3 + 1;
			}
			else{
				temp = temp / 2;
			}
			count++;
		}
		if (temp == 1 && count == n) {
			return i;
		}
		count = 0;
	}
}

uint64 getLargestNum(int k){
	if (k == 0) return 1;
	if (k == 1) return 2;
	return 2 * getLargestNum(k - 1);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	memset(cache, -1, sizeof(cache));

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		cout << "Case #" << test_case << "\n" << calc(n) << " " << getLargestNum(n) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}