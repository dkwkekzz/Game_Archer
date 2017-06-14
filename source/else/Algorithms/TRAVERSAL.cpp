#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n;

vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

void make_postorder(const vector<int>& preorder, const vector<int>& inorder) {
	int N = preorder.size();

	if (preorder.empty()) return;

	int root = preorder[0];
	int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	make_postorder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	make_postorder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	
	cout << root << endl;
}

int main() {
	vector<int> preorder, inorder;

	cin >> n;
	for (int i = 0; i < n; i++) {
		int e;
		cin >> e;
		preorder.push_back(e);
	}
	for (int i = 0; i < n; i++) {
		int e;
		cin >> e;
		inorder.push_back(e);
	}

	make_postorder(preorder, inorder);

}
