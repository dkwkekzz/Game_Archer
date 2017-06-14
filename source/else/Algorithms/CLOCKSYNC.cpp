#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int Clocks[16];
string Switch[10] = {
	"cccddddddddddddd",
	"dddcdddcdcdcdddd",
	"ddddcdddddcdddcc",
	"cdddccccdddddddd",
	"ddddddcccdcdcddd",
	"cdcdddddddddddcc",
	"dddcddddddddddcc",
	"ddddccdcddddddcc",
	"dcccccdddddddddd",
	"dddcccdddcdddcdd"
};

int onoff(int sw, int rest, int push) {
	if (push == 0) return rest;
	for (int i = 0; i < 16; i++) {
		if (Switch[sw][i] == 'c') {
			if (Clocks[i] == 0) rest++;
			Clocks[i] = (Clocks[i] + (3 * push)) % 12;
			if (Clocks[i] == 0) rest--;
		}
	}
	return rest;
}

int correcting(int count, int rest, int sw) {
	if (rest <= 0) return count;
	if (sw == 10) return 9999;
	int ret = 9999;
	for (int i = 0; i < 4; i++) {
		ret = min(ret, correcting(count + i, onoff(sw, rest, i), sw + 1));
		onoff(sw, rest, -i);
	}

	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int rest = 16;
		for (int j = 0; j < 16; j++) {
			cin >> Clocks[j];
			if (Clocks[j] == 12) {
				Clocks[j] = 0;
				rest--;
			}
		}
		cout << correcting(0, rest, 0) << endl;
	}
}