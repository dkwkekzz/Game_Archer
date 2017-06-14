#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAX = 2000000000 + 1;
int n, k, m;
int lis[500], cashe[501];
long long cashe2[501];

int LIS(int start) {
	if (start == n - 1) return 1;

	int &ret = cashe[start + 1];
	if (ret != -1) return ret;

	ret = 1;
	for (int i = start + 1; i < n; i++) 
		if (start == -1 || lis[start] < lis[i]) 
			ret = max(ret, 1 + LIS(i));
	return ret;
}

int count(int start) {
	if (LIS(start) == 1) return 1;

	long long &ret = cashe2[start + 1];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = start + 1; i < n; i++) {
		if ((start == -1 || lis[start] < lis[i]) && LIS(start) == LIS(i) + 1) {
			ret = min<long long>(MAX, (long long)ret + count(i));
		}
	}
	return ret;
}

string reconstruct(int start, int skip) {
	if (skip <= 0) return "!";
	for (int i = start + 1; i < n; i++) {
		if ((start == -1 || lis[start] < lis[i]) && LIS(start) == LIS(i) + 1) {
			if (skip <= count(i)) {
				int a = lis[i];
				char c[10];
				_itoa_s(a, c, 10);
				return " " + (string)c + reconstruct(i, skip);
			}
			else skip -= count(i);
		}
	}
	return "";
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	memset(cashe2, -1, sizeof(cashe2));
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> lis[i];
	}
	cout << reconstruct(-1, k) << endl;
}