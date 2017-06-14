#include <iostream>
#include <algorithm>
using namespace std;

int n;
int triangle[101][101], cashe[101][101];

int path(int y, int x) {
	int &ret = cashe[y][x];
	if (ret != -1) return ret;

	if (y == n - 1) return max(triangle[y][x], triangle[y][x + 1]);

	int ret = 0;
	return ret = max(path(y + 1, x), path(y + 1, x + 1));
}

int count(int y, int x) {
	int &ret = cashe[y][x];
	if (ret != -1) return ret;

	if (y == n - 1) return 1;

	int ret = 0;
	if (path(y + 1, x + 1) >= path(y + 1, x)) ret += count(y + 1, x + 1);
	if (path(y + 1, x + 1) <= path(y + 1, x)) ret += count(y + 1, x);

	return ret;
}