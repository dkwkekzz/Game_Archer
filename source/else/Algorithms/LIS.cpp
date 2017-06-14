#include <iostream>
#include <algorithm>
using namespace std;

int lis[100], cashe[100];
int n;

int lis2(int index) {
	int &ret = cashe[index];
	if (ret != -1) return ret;

	int ret = 0;
	for (int i = index + 1; i < n; i++) {
		if (index == -1 || lis[index] < lis[i])
			ret = max(ret, 1 + lis2(i));
	}
	return ret;
}