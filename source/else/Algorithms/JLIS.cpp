#include <iostream>
#include <algorithm>
using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int lis1[100], lis2[100], cashe[101][101];
int n, m;

int jlis(int indexA, int indexB) {
	int &ret = cashe[indexA + 1][indexB + 1];
	if (ret != -1) return ret;

	ret = 0;

	long long a = (indexA == -1 ? NEGINF : lis1[indexA]);
	long long b = (indexA == -1 ? NEGINF : lis2[indexB]);
	long long maxElement = max(a, b);

	for (int i = indexA + 1; i < n; i++) {
		if (maxElement < lis1[i])
			ret = max(ret, 1 + jlis(i, indexB));
	}
	for (int i = indexB + 1; i < m; i++) {
		if (maxElement < lis2[i])
			ret = max(ret, 1 + jlis(indexA, i));
	}
	return ret;
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> lis1[i];
	}
	for (int i = 0; i < m; i++) {
		cin >> lis2[i];
	}
 	cout << jlis(-1, -1) << endl;
}