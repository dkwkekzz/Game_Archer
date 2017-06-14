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
typedef long long int64;

const int MAX_N = 10000000 + 5, MOD = 1000000007;
int n;
int minFactor[MAX_N];
int factorCounter[MAX_N];
int64 pCache[4000][40];

void eratosthenes(){
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i < MAX_N; i++) minFactor[i] = i;
	int sqrtn = static_cast<int>(sqrt(MAX_N));
	for (int i = 2; i <= sqrtn; i++){
		if (minFactor[i] == i){
			for (int j = i * i; j <= MAX_N; j += i)
			if (minFactor[j] == j) minFactor[j] = i;
		}
	}
}

void countFactor(int n){
	while (n > 1){
		factorCounter[minFactor[n]]++;
		n /= minFactor[n];
	}
}
//a^b
int64 pow(int a, int b){
	if (b == 0) return 1;
	if (b == 1) return a;
	if (b & 1) return pow(a, b - 1)*a%MOD;
	if (a < 4000){
		int64 &ret = pCache[a][b];
		if (ret != -1) return ret;
		ret = pow(a, b / 2);
		return ret*ret%MOD;
	}
	else{
		int64 ret = pow(a, b / 2);
		return ret*ret%MOD;
	}
}

int64 solve(){
	int64 ret = 1;
	for (int i = n; i >= 2; i--){
		countFactor(i);
		if (factorCounter[i] & 1) factorCounter[i]--;
		ret *= pow(i, factorCounter[i]);
		ret %= MOD;
	}
	return ret;
}

bool IsSquare(int64 num) {
	int64 temp = (int64)(sqrt((double)num) + 0.5);
	return temp*temp == num;
}

int64 scaffolding(){
	int64 ret = 1;
	for (int64 i = n; i >= 1; i--){
		for (int64 j = n; j >= 1; j--){
			if (i == j) continue;
			int64 num = i*j;
			if (IsSquare(num)) ret = max(ret, num);
		}
	}
	return ret;
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(pCache, -1, sizeof(pCache));
	eratosthenes();
	while (scanf_s("%lld", &n)){
		if (!n) break;
		memset(factorCounter, 0, sizeof(factorCounter));
		printf("%lld\n", solve());
	}

	return 0;
}