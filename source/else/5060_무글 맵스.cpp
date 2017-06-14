#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int MAX_N = 200 + 5;
const double INF = 5e+8;
int64 n, c;
double location[MAX_N];
double cache[MAX_N][MAX_N];
double calcCache[MAX_N][MAX_N];

double calcError(int here, int there){
	double &ret = calcCache[here][there];
	if (ret > -0.5) return ret;

	ret = 0;
	for (int k = there + 1; k < here; k++){
		double e = location[there] + (location[here] - location[there])*(k - there) / (here - there);
		ret += static_cast<double>(abs(location[k] - e));
	}
	return ret;
}

double getMinError(int here, int there, int _c){
	if (here == n && there == n - 1 && _c == c) {
		cout << "stop" << endl;
		return 0;
	}
	if (here == n || _c == c) return INF;

	double &ret = cache[there][_c];
	if (ret > -0.5) return ret;

	return ret = min(getMinError(here + 1, there, _c)
		, calcError(here, there) + getMinError(here + 1, here, _c + 1));
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	int t; cin >> t;
	for (int tc = 0; tc < t; tc++){
		memset(cache, -1, sizeof(cache));
		memset(calcCache, -1, sizeof(calcCache));
		cin >> n >> c;
		for (int i = 0; i < n; i++) cin >> location[i];
		printf("%.4lf\n", getMinError(1, 0, 1) / static_cast<double>(n));
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}