#include <iostream>
#include <algorithm>
using namespace std;
//n: 과목 수 k: 들어야 할 과목 수 m: 학기 수 l: 학기당 최대 과목 수
int n, k, m, l;
int R[12], C[10];
int cashe[50][50];

int graduation(int session, int complete, int maxN, int k){
	if (k == 0) return session;
	if (maxN <= 0) graduation(session + 1, complete, l, k);
	if (session == m) return 0;

	int &ret = cashe[session][complete];
	if (ret != -1) return ret;

	ret = 0;
	for (int subject = 0; subject < n; subject++) {
		if (((1 << subject) & ~complete) && ((1 << subject) & C[session]) && ((R[subject] & complete) || R[subject] == 0)) {
			ret = max(ret, graduation(session, complete | (1 << subject), maxN - 1, k - 1));
		}
	}
	ret = max(ret, graduation(session + 1, complete, l, k));

	return ret;
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	memset(R, 0, sizeof(R));
	memset(C, 0, sizeof(C));
	cin >> n >> k >> m >> l;
	for (int i = 0; i < n; i++) {
		int r;
		cin >> r;
		for (int j = 0; j < r; j++) {
			int ri;
			cin >> ri;
			R[i] |= (1 << ri);
		}
			
	}
	for (int i = 0; i < m; i++) {
		int c;
		cin >> c;
		for (int j = 0; j < c; j++) {
			int ci;
			cin >> ci;
			C[i] |= (1 << ci);
		}
	}
	int ret = graduation(0, 0, l, k);
	if (ret == 0) cout << "Impossible" << endl;
	else cout << ret << endl;
}