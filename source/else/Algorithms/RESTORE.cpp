#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int MAX_N = 15;
string partial[MAX_N];
int k;
int cashe[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];

int overlapF(int last, int now) {
	int &ret2 = overlap[last][now];
	if (ret2 != -1) return ret2;

	int lastlen = partial[last].size();
	int nowlen = partial[now].size();
	int len = (lastlen >= nowlen ? nowlen : lastlen);
	for (int i = 0; i < len; i++)
		if (partial[last].substr(lastlen - len + i, lastlen) == partial[now].substr(0, len - i))
			return ret2 = len - i;
	return ret2 = 0;
}

int restore(int last, int used) {
	if (used == (1 << k) - 1) return 0;

	int &ret = cashe[last][used];
	if (ret != -1) return ret;
	
	ret = 0;
	for (int i = 0; i < k; i++) 
		if ((used & (1 << i)) == 0) 
			ret = max(ret, overlapF(last, i) + restore(i, used + (1 << i)));
	return ret;
}

string reconstruct(int last, int used) {
	if (used == (1 << k) - 1) return "";

	for (int i = 0; i < k; i++) {
		if ((used & (1 << i)) == 0) {
			if (restore(last, used) == (overlapF(last, i) + restore(i, used + (1 << i)))) {
				return partial[i].substr(overlap[last][i]) + reconstruct(i, used + (1 << i));
			}
		}
	}
	return "#";
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	memset(overlap, -1, sizeof(overlap));
	cin >> k;
	for (int i = 0; i < k; i++) 
		cin >> partial[i];
	
	int ret = 0;
	int temp = 0;
	for (int i = 0; i < k; i++) {
		int cand = restore(i, (1 << i));
		if (cand > ret) {
			ret = cand;
			temp = i;
		}
	}

	cout << partial[temp] + reconstruct(temp, (1 << temp)) << endl;
}