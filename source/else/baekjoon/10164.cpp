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

int n, m, k;

typedef unsigned long long uint64;
typedef long long int int64;
const int INF = 987654321, MOD = 1000000007, MAX_N = 20005;
int64 f_c[MAX_N], f_c_inv[MAX_N];

void input(){
	cin >> n >> m >> k;
}

int64 inverse(int64 n, int64 m){
	if (m == 0) return 1;

	int64 ret = inverse(n, m >> 1);
	ret = (ret * ret) % MOD;
	if (m & 1) ret = (ret * n) % MOD;

	return ret;
}

int64 bino(int64 n, int64 r){
	if (r == 0 || n == r) return 1;

	return ((f_c[n] * f_c_inv[r]) % MOD * f_c_inv[n - r]) % MOD;
}

void preCalc(){
	f_c[0] = 1, f_c_inv[0] = 1;
	for (int64 i = 1; i < MAX_N; i++){
		f_c[i] = (f_c[i - 1] * i) % MOD;
		f_c_inv[i] = inverse(f_c[i], MOD - 2) % MOD;
	}
}

long long solve(){
	int y, x;
	if (k != 0) y = k / m + 1, x = k % m;
	else return bino(m + n - 2, m - 1);
	if (y > 0 && x == 0) y--, x = m;

	return bino(y + x - 2, x - 1) * bino(n - y + m - x, m - x);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);
	cin.sync_with_stdio(false);
	preCalc();
	input();

	cout << solve() << endl;
	return 0;
}
