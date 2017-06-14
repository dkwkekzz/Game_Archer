#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	//A[0..pos]의 부분합을 구한다.
	int sum(int pos) {
		pos++;

		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}
	//A[pos]에 val을 더한다.
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};