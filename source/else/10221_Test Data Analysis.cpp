#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long lint;

const int MAX_N = 1005, MOD = 1000000007, RT = 1500000;
int tc, n, d, a[MAX_N], b[MAX_N], rt[RT*2][2];
vector<int> sum;
/*lint f_c[MAX_N], f_c_inv[MAX_N];

lint myPow(int n, int e){
	if (e == 0) return 1;
	if (e == 1) return n;
	if (e & 1) return myPow(n, e - 1)*n%MOD;
	lint ret = myPow(n, e >> 1);
	return ret*ret%MOD;
}
inline lint inverse(int n){
	return myPow(n, MOD - 2);
}
lint bino(int n, int r){
	if (r == 0 || n == r) return 1;
	return ((f_c[n] * f_c_inv[r]) % MOD * f_c_inv[n - r]) % MOD;
}
void precalc(){
	f_c[0] = 1, f_c_inv[0] = 1;
	for (lint i = 1; i < MAX_N; i++){
		f_c[i] = (f_c[i - 1] * i) % MOD;
		f_c_inv[i] = inverse(f_c[i]) % MOD;
	}
}*/

void solve(int i, int pa, int pb){
	if (i == n){
		cout << rt[d + RT][i % 2] << endl; return;
	}
	int na = pa, nb = pb;
	sum = vector<int>(1, 1);
	for (int j = na + 1; j <= nb; j++) sum.push_back((sum.back() + rt[j][i%2]) % MOD);
	na += a[i], nb += b[i];
	int ai = na, bi = nb, k = 0;
	while (ai <= bi){ 
		rt[ai++][(i + 1) % 2] = rt[bi--][(i + 1) % 2] 
			= sum.size() > k ? sum[k++] : sum[sum.size() - 1];
	}
	solve(i + 1, na, nb);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//precalc();
	cin.sync_with_stdio(false);
	for (cin >> tc; tc > 0; tc--){
		memset(rt, 0, sizeof(rt));
		cin >> n >> d;
		for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
		solve(0, RT, RT);
	}
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}