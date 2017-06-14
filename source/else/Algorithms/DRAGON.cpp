#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

const int MAX = 1000000000 + 1;
int len[51];
int n, p, l;

void precalc() {
	len[0] = 1;
	for (int i = 1; i <= 50; i++) 
		len[i] = min(MAX, len[i - 1] * 2 + 2);
}

char expand(const string &dragonCurve, int generations, int skip) {
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}

	for (int i = 0; i < dragonCurve.size(); i++) {
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= len[generations]) skip -= len[generations];
			else if (dragonCurve[i] == 'X') return expand("X+YF", generations - 1, skip);
			else if (dragonCurve[i] == 'Y') return expand("FX-Y", generations - 1, skip);
		}
		else if (skip > 0) skip--;
		else return dragonCurve[i];
	}
	return '@';
}

int main() {
	cin >> n >> p >> l;
	precalc();
	for (int i = 0; i < l; i++) {
		cout << expand("FX", n, p + i - 1);
	}
	cout << endl;
}
