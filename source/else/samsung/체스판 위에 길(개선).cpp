#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

int n, m, k;

long long f_c[20001], f_c_inv[20001];

struct obstacle{
	int x, y;
	long long v;
}o[2001];

long long inverse(long long n, long long m){
	if (m == 0) return 1;

	long long ret = inverse(n, m >> 1);
	ret = (ret * ret) % MOD;
	if (m & 1) ret = (ret * n) % MOD;

	return ret;
}

long long bino(long long n, long long r){
	if (r == 0 || n == r) return 1;

	return ((f_c[n] * f_c_inv[r]) % MOD * f_c_inv[n - r]) % MOD;
}

long long solve(int k){
	long long &ret = o[k].v;
	if (ret != -1) return ret;

	long long y = o[k].y, x = o[k].x;
	long long temp = 0;
	ret = bino(y + x - 2, y - 1);

	for (int i = 0; i < k; i++){
		long long oy = o[i].y, ox = o[i].x;

		if (ox > x) continue;
		if (oy == y && ox == x) break;
		temp = (temp + (solve(i) * bino((y - oy) + (x - ox), (y - oy)) % MOD) % MOD) % MOD;
	}

	return ret = (ret - temp + MOD) % MOD;
}

void preCalc(){
	f_c[0] = 1, f_c_inv[0] = 1;
	for (long long i = 1; i < 20001; i++){
		f_c[i] = (f_c[i - 1] * i) % MOD;
		f_c_inv[i] = inverse(f_c[i], MOD - 2) % MOD;
	}
}

bool compare(obstacle& a, obstacle& b){
	return a.y < b.y || a.y == b.y && a.x < b.x;
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	preCalc();

	int TC;

	cin >> TC;
	for (int i = 1; i <= TC; i++){
		cin >> n >> m >> k;
		for (int j = 0; j < k; j++){
			cin >> o[j].y >> o[j].x;
			o[j].v = -1;
		}
		o[k].y = n;
		o[k].x = m;
		o[k].v = -1;
		sort(o, o + k, compare);

		cout << "Case #" << i << "\n" << solve(k) << endl;
	}
}