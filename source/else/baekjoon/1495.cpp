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

const int INF = 987654321, MAX_N = 101, MAX_M = 1001;
int n, s, m;
int V[MAX_N];

int control(int v){
	return ((v > m || v < 0) ? -INF : v);
}

int solve(){
	int C[MAX_N][MAX_M]; memset(C, -1, sizeof(C));
	C[0][s] = s;
	for (int ni = 0; ni < n; ni++){
		for (int mi = 0; mi <= m; mi++){
			if (C[ni][mi] < 0) continue;
			int vUp = control(C[ni][mi] + V[ni]), vDown = control(C[ni][mi] - V[ni]);
			if (vUp >= 0) C[ni + 1][vUp] = max(C[ni + 1][vUp], vUp); 
			if (vDown >= 0) C[ni + 1][vDown] = max(C[ni + 1][vDown], vDown);
		}
	}

	return *max_element(C[n], C[n] + MAX_M);
}

int main(){
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin >> n >> s >> m;
	for (int i = 0; i < n; i++){
		cin >> V[i];
	}

	cout << solve() << endl;

	return 0;
}