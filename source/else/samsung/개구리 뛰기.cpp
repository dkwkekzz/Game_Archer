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

const int INF = 1234567890;

int n, k;

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오.
		cin >> n;

		int* stone = new int[n + 2];

		stone[0] = 0, stone[n + 1] = INF; 
		for (int i = 1; i <= n; i++) cin >> stone[i];
		cin >> k;

		int jump = 0, there = 1;
		for (int here = 0; here < n; here = there - 1){
			there = here + 1;
			while (stone[there] - stone[here] <= k) there++;

			if (there == here + 1) {
				jump = -1; break;
			}

			jump++;
		}

		// 이 부분에서 정답을 출력하십시오.
		cout << "Case #" << test_case << "\n" << jump << endl;

		delete[] stone;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}