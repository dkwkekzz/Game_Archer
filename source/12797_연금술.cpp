#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long lint;

const int MAX_M = 1005, MOD = 1000000007;
int n, m, a[MAX_M];
lint D[MAX_M], P[MAX_M][MAX_M], PI[MAX_M][MAX_M], V[MAX_M][MAX_M], dp[MAX_M][MAX_M], temp[MAX_M][MAX_M];

lint myPow(lint a, lint e){
	if (e == 0) return 1;
	if (e == 1) return a;
	if (e & 1) return (myPow(a, e - 1)*a) % MOD;
	lint ret = myPow(a, e / 2);
	return ret*ret%MOD;
}

inline lint inverse(lint a){
	return myPow(a, MOD - 2);
}

int makeMatrixes(){
	//D
	for (int i = 0, value = a[i]; i < m; value = a[++i]) D[i] = myPow(a[i], n);
	//V
	for (int i = 0, value = a[i]; i < m; value = a[++i])
	for (int j = i; j < m; j++) V[i][j] = value;
	//P
	for (int i = 0, lamda = a[0]; i < m; lamda = a[++i] - a[i - 1]){
		for (int vi = 0; vi < m; vi++) {
			V[vi][vi] -= lamda;
			V[vi][vi] += MOD;
			V[vi][vi] %= MOD;
		}
		for (int j = i; j >= 0; j--){
			dp[j][i] = (dp[j + 1][i] + P[j + 1][i]) % MOD;
			if (!V[j][j]) P[j][i] = 1;
			else P[j][i] = (((-a[j] + MOD) * dp[j][i]) % MOD) * inverse(V[j][j]) % MOD;
		}
	}
	//PI m_col
	PI[m - 1][m - 1] = 1;
	for (int i = m - 1; i >= 1; i--){
		int value = PI[i][m-1];
		for (int j = i - 1; j >= 0; j--){ 
			PI[j][m - 1] -= (value*P[j][i]) % MOD;
			PI[j][m - 1] += MOD;
			PI[j][m - 1] %= MOD;
		}
	}
	//P*D
	for (int i = 0; i < m; i++){
		for (int j = 0; j < m; j++){
			temp[i][j] = (P[i][j] * D[j]) % MOD;
		}
	}
	//temp*PI
	lint ret = 0;
	for (int i = 0; i < m; i++){
		for (int j = 0; j < m; j++){
			ret += (temp[i][j] * PI[j][m - 1]) % MOD;
			ret %= MOD;
		}
	}
	return ret;
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < m; i++) cin >> a[i];
	cout << makeMatrixes() << endl;

	return 0;
}