#include <iostream>
using namespace std;

const int MAXN = 20;
int n;
int explodes[MAXN];

bool isStable(int set) {
	for (int i = 0; i < n; i++)
		if ((set & (1 << i)) && (set & explodes[i]))
			return false;
	return true;
}

int countStableSet() {
	int ret = 0;
	for (int set = 1; set < (1 << n); set++) {
		if (!isStable(set)) continue;
		bool canExtend = false;
		for (int add = 0; add < n; add++)
			if ((set & (1 << add)) == 0 && (set & explodes[add]) == 0) {
				canExtend = true;
				break;
			}
		if (!canExtend) ret++;
	}
	return ret;
}