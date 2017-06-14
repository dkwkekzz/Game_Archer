#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int n, capacity;
int volume[100], need[100];
int cashe[1001][100];
string name[100] = {
	"laptop",
	"camera",
	"xbox",
	"coffeeGrinder",
	"dumbell",
	"encyclopedia"
};

int pack(int capacity, int item) {
	if (item == n) return 0;

	int &ret = cashe[capacity][item];
	if (ret != -1) return ret;

	ret = pack(capacity, item + 1);
	if (capacity >= volume[item])
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	return ret;
}

void reconstruct(int capacity, int item, vector<string> &packed) {
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) {
		reconstruct(capacity, item + 1, packed);
	}
	else {
		packed.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, packed);
	}
		
}
