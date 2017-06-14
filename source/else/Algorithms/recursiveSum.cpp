#include <iostream>
#include <vector>
using namespace std;

int n;

int recursiveSum(int n) {
	if (n == 1) return 1;
	return recursiveSum(n - 1) + n;
}

void printVector(const vector<int> &selected) {
	cout << selected[0] << " " << selected[1] << " " << selected[2] << " " << selected[3] << endl;
}

void choiceElement(vector<int> &selected, int index) {
	if (selected.size() == 4) {
		printVector(selected);
		return;
	}
	if (index > n) return;
	selected.push_back(index);
	choiceElement(selected, ++index);
	selected.pop_back();
	choiceElement(selected, index);
}

void pick(int n, vector<int> picked, int toPick) {
	if (toPick == 0) {
		printVector(picked);
		return;
	}
	int smallest = picked.empty() ? 0 : picked.back() + 1;
	for (int next = smallest; next < n; ++next) {
		picked.push_back(next);
		pick(n, picked, toPick - 1);
		picked.pop_back();
	}
}

void main() {
	cin >> n;
	//cout << recursiveSum(n) << endl;

	vector<int> selected;
	choiceElement(selected, 0);
}

