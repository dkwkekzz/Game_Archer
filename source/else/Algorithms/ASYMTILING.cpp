#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
int n;
int cashe[101], cashe2[101];

int tiling(int width) {
	if (width <= 1) return 1;

	int &ret = cashe[width];
	if (ret != -1) return ret;

	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

int asymmetric(int width) {
	int ret = tiling(n);
	if (n % 2 == 0) {
		ret = (ret - tiling(n / 2) + MOD) % MOD;
		ret = (ret - tiling((n - 2) / 2) + MOD) % MOD;
	}
	else ret = (ret - tiling((n - 1) / 2) + MOD) % MOD;
	return ret;
}

int asymmetric2(int width) {
	if (width <= 2) return 0;

	int &ret = cashe[width];
	if (ret != -1) return ret;

	ret = asymmetric2(width - 2) % MOD;
	ret = (ret + asymmetric2(width - 4)) % MOD;
	ret = (ret + tiling(width - 3)) % MOD;
	ret = (ret + tiling(width - 3)) % MOD;
	return ret;
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	cin >> n;

	cout << asymmetric(n) << endl;
}