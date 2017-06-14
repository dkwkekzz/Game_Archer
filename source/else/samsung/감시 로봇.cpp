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

const int MAX_N = 100005, MAX_L = 1000000000;
int n, r, l;
int x[MAX_N];

void init(){
	memset(x, 0, sizeof(x));
}

void input(){
	cin >> n >> r >> l;
	for (int i = 0; i < n; i++) cin >> x[i];
}

bool check(int d){
	int here = -MAX_L;
	for (int i = 0; i < n; i++){
		if (here == -MAX_L && (x[i] + d > -r) && (x[i] - d <= r)) here = min(x[i] + d, r);
		else if ((x[i] + d >= here - 2 * r) && (x[i] - d <= here + 2 * r)) here = min(x[i] + d, here + 2 * r);
		
		if (here >= l - r) return 1; 
	}

	return 0;
}

int solve(){
	int ret = MAX_L;
	if (2 * r * n < l) return -1;
	int left = 0, right = MAX_L;
	while (left <= right){
		int mid = left + (right - left) / 2;
		if (check(mid)){
			right = mid - 1;
			ret = min(ret, mid);
		}
		else left = mid + 1;
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

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}