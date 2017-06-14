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
const int INF = 987654321, MAX_N = 31;
int n;

void input(){
	cin >> n;
}

uint64 solve(){
	vector<uint64> C(MAX_N, 0);
	C[n] = 1; 
	for (int i = n; i >= 0; i -= 2){
		if (i >= 2) C[i - 2] += C[i] * 3;
		for (int j = 1; j < n / 2; j++){
			if (i >= (2 + j * 2)) C[i - (2 + j * 2)] += C[i] * 2;
		}
	}

	return C[0];
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	input();

	cout << solve() << endl;

	return 0;
}