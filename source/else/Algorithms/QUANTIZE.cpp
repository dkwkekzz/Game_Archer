#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int INF = 987654321;

int n;
int A[101], pSum[101], pSqSum[101];

void precalc() { //A를 정렬하고 각 부분합을 계산한다.
	sort(A, A + n);
	pSum[0] = A[0];
	pSqSum[0] = A[0] * A[0];
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + A[i] * A[i];
	}
}

int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
	//평균을 반올림한 값으로 이 수들을 표현한다.
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	//sum(A[i]-m)^2를 전개한 결과를 부분 합으로 표현
	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}

int cashe[101][11];
int quantize(int from, int parts) {
	if (from == n) return 0;
	if (parts == 0) return INF;
	int &ret = cashe[from][parts];
	if (ret != -1) return ret;
	ret = INF;

	for (int partSize = 1; from + partSize <= n; partSize++) 
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
	return ret;
}