#include <iostream>
#include <algorithm>
using namespace std;

int n;
int cashe[100];

int tiling(int rest) {
	if (rest == 0) return 1;

	int &ret = cashe[rest];
	if (ret != -1) return ret;

	ret = 0;
	return ret = tiling(rest - 2) + tiling(rest - 1);
}