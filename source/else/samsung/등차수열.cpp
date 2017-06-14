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

const uint64 MAX_N = 1000000000001;

int n;

vector<uint64> input(){
	cin >> n;
	vector<uint64> a(n);
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}

	return a;
}

uint64 minFactor(uint64 a){
	uint64 sqrtn = sqrt(a), ret;
	vector<uint64> minF(sqrtn + 1, 1);
	for (int i = 2; i <= sqrtn; i++){
		if (a % i == 0) {
			minF[i]++;
			a = a / i;
			sqrtn = sqrt(a);
			i = 1;
		}
	}

	if (a < minF.size()) {
		minF[a]++; ret = 1;
	}
	else ret = 2;

	for (int i = 2; i < minF.size(); i++){
		ret *= minF[i];
	}

	return ret;
}

/*uint64 solve(const vector<uint64> a){
	if (a.size() == 1) return minFactor(a[0]);

	vector<uint64> b;
	for (int i = 1; i < a.size(); i++){
		uint64 temp = (a[i] < a[i - 1] ? a[i - 1] - a[i] : a[i] - a[i - 1]);
		if (temp != 0) b.push_back(temp);
	}
	if (b.size() == 0) return minFactor(a[0]);

	return solve(b);
}*/

uint64 solve(const vector<uint64> a){
	uint64 minValue = MAX_N, minIndex = 0, ret = 0;
	for (int i = 0; i < a.size(); i++){
		if (minValue > a[i]){
			minValue = a[i];
			minIndex = i;
		}
	}

	uint64 n = minValue, sqrtn = sqrt(n);
	vector<uint64> minFactor(sqrtn + 1, 1);
	for (int i = 2; i <= sqrtn; i++){
		if (n % i == 0) {
			bool canDivide = true;
			for (int ai = 0; ai < a.size(); ai++){
				if (a[ai] % i != 0){
					canDivide = false; break;
				}
			}

			if (canDivide){
				minFactor[i]++;
				n = n / i;
				sqrtn = sqrt(n);
				i = 1;
			}
		}
	}

	if (n < minFactor.size()) {
		minFactor[n]++; ret = 1;
	}
	else ret = 2;

	for (int i = 2; i < minFactor.size(); i++){
		ret *= minFactor[i];
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		vector<uint64> a(input());

		int isZero = 0;
		for (int i = 1; i < a.size(); i++){
			a[i - 1] = (a[i] < a[i - 1] ? a[i - 1] - a[i] : a[i] - a[i - 1]);
			if (a[i - 1] == 0) isZero++;
		}
		a.pop_back();

		if (isZero == a.size()) {
			cout << "Case #" << test_case << "\n" << 1 << endl;
		}
		else if(isZero > 0) {
			cout << "Case #" << test_case << "\n" << 0 << endl;
		}
		else cout << "Case #" << test_case << "\n" << solve(a) << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}
