#include <iostream>
#include <vector>
using namespace std;

int n;
int p[50000];
int q[50000];

struct TreeNode {
	int index;
	TreeNode* left;
	TreeNode* right;
};

void printTree(TreeNode* tree) {
	cout << tree->index + " ";
	//if (left != NULL) printTree(tree->left);
	//if (right != NULL) printTree(tree->right);
	cout << endl;
}

TreeNode* setTree(int root, int e) {
	TreeNode* tree = new TreeNode();
	tree->index = e;

	if (root == -1) return tree;
	int delta = isNerd(root, e);
	switch (delta) {
	case 0:
		return;
	case 1:
		
	}

}

void nerd() {
	TreeNode* nerdTree = new TreeNode();
	nerdTree->index = -1;
	for (int i = 0; i < n; i++) {
		nerdTree = setTree(nerdTree->index, i);
		cout << nerdTree->index << endl;
	}
}

int isNerd(int root, int e) { // 3: 너드 교체, 2: 오른쪽 검사, 1: 왼쪽 검사, 0: 해당사항 없음
	int delta = 0; 
	if (p[root] > p[e]) delta + (1 << 1);
	if (q[root] > q[e]) delta + 1;
	
	return delta;
}

void swapTree() {

}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> p[i] >> q[i];
	}

	nerd();

	cout << "end" << endl;
}