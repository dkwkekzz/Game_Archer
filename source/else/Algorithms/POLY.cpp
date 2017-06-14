#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 10000000;
int n;
int cashe[101][101];

int mypoly(int pre, int rec) {
	if (rec == 0) return 1;

	int &ret = cashe[pre][rec];
	if (ret != -1) return ret;
	
	ret = 0;
	for (int next = 1; next <= rec; next++) {
		if (pre == 0) ret = (ret + mypoly(next, rec - next)) % MOD;
		else ret = (ret + mypoly(next, rec - next) * (pre - 1 + next)) % MOD;
	}
	return ret;
}

int poly(int n, int first) { //n개의 첫 줄이 first개인 정사각형을 포함하는 폴리오미노의 수
	if (n == first) return 1;

	int &ret = cashe[n][first];
	if (ret != -1) return ret;
	
	ret = 0;
	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1;
		add *= poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	cin >> n;
	cout << poly(0, n) << endl;
}