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
const int MAX_N = 105;
int n;
int64 N[MAX_N], cache[MAX_N][25];

int64 calc(int64 index, int64 sum){
	if (sum < 0 || sum > 20) return 0; 
	if (index == n - 1) return sum == N[index];

	int64 &ret = cache[index][sum];
	if (ret != -1) return ret;

	return ret = calc(index + 1, sum + N[index]) + calc(index + 1, sum - N[index]);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(cache, -1, sizeof(cache));
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) scanf_s("%d", &N[i]);
	printf("%lld\n", calc(1, N[0]));

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}