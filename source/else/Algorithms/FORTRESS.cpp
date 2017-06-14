#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int x[100];
int y[100];
int r[100];
TreeNode* mainFort;

struct TreeNode {
	vector<TreeNode*> children;
};

void addList(TreeNode* addFort) {
	if (mainFort->children.empty()) mainFort->children.push_back(addFort);

	for (int i = 0; i < mainFort->children.size(); i++) {
		
	}
	
}

int main() {

}