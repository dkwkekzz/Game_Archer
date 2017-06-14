#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*int fence[200];

int trim(int begin, int end) {
	if (end == begin) {
		return fence[begin];
	}
	if ((end + begin) % 2 == 0) {
		int x = end - 1;
		int y = min(fence[x], fence[end]);
		int size = (end - x + 1) * y;
		while (--x >= begin) {
			if(fence[x] >= y)	size = (end - x + 1) * y;
			else {
				size = max(size, fence[x] * (end - x + 1));
				y = fence[x];
			}
		}
		return max(max(trim(begin, end - 1), fence[end]), size);
	}

	int ret = 0;
	int half = (begin + end) / 2;
	ret = max(trim(begin, half), trim(half + 1, end));

	int y = min(fence[half], fence[half + 1]);
	int lx = 1, rx = 1, x = 2;
	int left = 0, right = 0;
	int size = max(size, x * y);
	while (left != -1 || right != -1) {
		x = lx + rx;
		if (half + 1 + rx > end) right = -1;
		if (half - lx < begin) left = -1;
		if (right != -1) right = fence[half + 1 + rx];
		if (left != -1) left = fence[half - lx];
		if (y <= right) {
			rx++;
			size = ++x * y;
		}
		if (y <= left) {
			lx++;
			size = ++x * y;
		}
		if (y > right && y > left) {
			if (size <= x * max(right, left)) {
				y = max(right, left);
				size = x * max(right, left);
			}
			else {
				left = -1;
				right = -1;
			}
		}
	}
	ret = max(ret, size);

	return ret;
}*/

vector<int> h;

int solve(int left, int right) {
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right));
	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);
	ret = max(ret, height * 2);
	while (left < lo || hi < right) {
		if (hi < right && (left == lo || h[lo - 1] < h[hi + 1])) {
			hi++;
			height = min(height, h[hi]);
		}
		else {
			lo--;
			height = min(height, h[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n;
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> fence[j];
		}
		cout << trim(0, n - 1) << endl;
	}
}