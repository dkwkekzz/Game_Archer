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
typedef unsigned long long uint64;
const int INF = 987654321, MAX_N = 1000001;
int n;
int64 S[MAX_N];

void input(){
	cin >> n;
	for (int i = 0; i < n; i++) cin >> S[i];
}

int64 solve(){
	int64 maxValue = S[0], sum = S[0];
	for (int i = 1; i < n; i++){
		if (sum < 0) sum = 0;
		sum += S[i];
		maxValue = max(maxValue, sum);
	}

	return maxValue;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	input();

	cout << solve() << endl;

	return 0;
}