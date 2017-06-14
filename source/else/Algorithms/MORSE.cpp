#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int M = 1000000000 + 100;
int bino[201][201];

void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++) {
			bino[i][j] = min(M, bino[i - 1][j] + bino[i - 1][j - 1]);
		}
	}
}

string generate(int n, int m, int skip) {
	if (n == 0) return string(m, 'o');

	if (skip < bino[n + m - 1][n - 1])
		return "-" + generate(n - 1, m, skip);
	return "o" + generate(n, m - 1, skip - bino[n + m - 1][n - 1]);
}