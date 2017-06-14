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
typedef unsigned long long uint64;
const int INF = 987654321, MAX_N = 5001, MAX_M = 10001;
int n = -1, nm = -1;
double m = -0.5;
int prices[MAX_N], calories[MAX_N];

void input(){
	cin >> n >> m;
	nm = static_cast<int>(m * 100.0 + 0.5);
	for (int i = 0; i < n; i++){
		double p; cin >> calories[i] >> p;
		prices[i] = static_cast<int>(p * 100.0 + 0.5);
	}
}

int solve(){
	vector<int> C(MAX_M, 0);
	int ret = 0;
	for (int amount = 1; amount <= nm; amount++){
		for (int i = 0; i < n; i++){
			if (amount >= prices[i]){
				C[amount] = max(C[amount], C[amount - prices[i]] + calories[i]);
			}
		}
		ret = max(ret, C[amount]);
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	while (n != 0 || m != 0.00){
		input();
		if (n != 0 || m != 0.00) cout << solve() << endl;
	}

	return 0;
}