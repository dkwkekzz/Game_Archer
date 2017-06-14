#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int MAX_N = 100000 + 5;
int64 n;
int64 h[MAX_N];

int64 getMaxSize(int left, int right){
	int64 mid = (right + left)/2;
	if ((right - left) == 0) return h[left];

	int64 ret = 0, l = 0, r = 0;
	if ((right - left + 1) & 1) l = right - 1, r = right;
	else l = mid, r = mid + 1;
	ret = max(getMaxSize(left, l), getMaxSize(r, right));

	int64 height = min(h[l], h[r]);
	ret = max(ret, 2 * height);
	while (l > left || r < right){
		if (l > left && (r==right || h[l - 1] >= h[r + 1])){
			height = min(height, h[--l]);
		}
		else if (r < right || l == left){
			height = min(height, h[++r]);
		}
		else break;
		ret = max(ret, (r-l+1)*height);
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	while (scanf_s("%lld", &n)){
		if (!n) break;
		for (int i = 1; i <= n; i++) cin >> h[i];
		cout << getMaxSize(1, n) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}