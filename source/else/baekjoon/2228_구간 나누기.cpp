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
typedef long long int64;

const int INF = 987654321, MAX_N = 105;
int n, m;
int S[MAX_N], sum[MAX_N];
int cache[MAX_N][MAX_N][MAX_N];

void preCalc(){
	sum[0] = S[0];
	for (int i = 1; i < n; i++)
		sum[i] = sum[i - 1] + S[i];
}

void init(){
	memset(cache, -1, sizeof(cache));
}

void input(){
	scanf_s("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf_s("%d", &S[i]);
}

int breakSection(int from, int interval, int section){
	if (section == m) return 0;
	if (from >= n - 1 && section < m - 1) return -INF;

	int &ret = cache[from][interval][section];
	if (ret != -1) return ret;

	ret = -INF;
	for (int i = from; i < n; i++){
		if (interval > section){
			if (from == 0) ret = max(ret, sum[i] + breakSection(i + 1, interval, section + 1));
			else ret = max(ret, sum[i] - sum[from - 1] + breakSection(i + 1, interval, section + 1));
		}
		else{
			ret = max(ret, breakSection(i + 1, interval + 1, section));
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	init(); input(); preCalc();
	cout << max(breakSection(0, 0, 0), breakSection(0, 1, 0)) << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}