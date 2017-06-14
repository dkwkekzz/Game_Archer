#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	//A[0..pos]�� �κ����� ���Ѵ�.
	int sum(int pos) {
		pos++;

		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}
	//A[pos]�� val�� ���Ѵ�.
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};