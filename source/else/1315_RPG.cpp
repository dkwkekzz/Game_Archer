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
const int MAX_N = 100 + 5, MAX_V = 1000 + 5;
int n;
int q[MAX_N][3], cache[MAX_V][MAX_V];

bool canComplete(int qi, int STR, int INT){
	return q[qi][0] <= STR || q[qi][1] <= INT;
}

int play(int STR, int INT){
	if (STR >= 1000 || INT >= 1000) return n;

	int &ret = cache[STR][INT];
	if (ret != -1) return ret;

	ret = 0;
	int pnt = 2 - STR - INT;
	for (int i = 0; i < n; i++)
	if (canComplete(i, STR, INT)) {
		ret++;
		pnt += q[i][2];
	}
	for (int sp = 0, ip = pnt; sp <= pnt; sp++, ip--)
		ret = max(ret, play(STR + sp, INT + ip));
	return ret;
}

int main(int argc, char** argv) {
	memset(cache, -1, sizeof(cache));
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
		scanf_s("%d %d %d", &q[i][0], &q[i][1], &q[i][2]);
	printf("%d\n", play(1, 1));

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}