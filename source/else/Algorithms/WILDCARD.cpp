#include <iostream>
#include <vector>
#include <string>
using namespace std;

int cashe[100][100];
string w, s;

bool match(int y, int x) {
	int &ret = cashe[y][x];
	if (ret != -1) return ret;

	if (w.size() - 1 == x && w[x] == '*') return ret = true;
	if (w.size() == x && s.size() == y) return ret = true;
	else if (w.size() == x || s.size() == y) return ret = false;

	if (w[x] == s[y] || w[x] == '?') return match(y + 1, x + 1);
	if (w[x] == '*') {
		for (int skip = 0; skip + y <= S.size(); skip++)
			if (match(skip + y, x + 1)) return ret = true;
	}
	return ret = false;
}

string W, S;

bool matchMemorized(int w, int s) {
	int &ret = cashe[w][s];
	if (ret != -1) return ret;

	while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}
	if (w == W.size()) return ret = (s == S.size());
	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); skip++)
			if (matchMemorized(w + 1, s + skip)) return ret = 1;
	}
	return ret = 0;
}