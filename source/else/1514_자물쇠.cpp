#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int INF = 987654321, MAX_N = 105;
int n;
string key, nKey;
int subKey[MAX_N];
int cache[MAX_N][20][20][20];

bool check(){
	for (int i = 0; i < n; i++) if (subKey[i] != 0) return 0;
	return 1;
}

int setKey(int index, int counter, int e1, int e2){
	if (check()) return 0;
	
	int &ret = cache[index][counter + 10][e1 + 10][e2 + 10];
	if (ret != -1) return ret;

	ret = INF;
	if (counter == 0) return ret = setKey(index + 1, subKey[index + 1], subKey[index + 2], subKey[index + 3]);
	int delta = (counter > 0 ? 1 : -1);
	for (int press = 1; (press <= counter*delta) && (press <= 3); press++){
		for (int i = 0; i < 3; i++){
			subKey[index + i] -= press*delta;
			int sub = subKey[index + i];
			int delta_sub = (sub >= 0), temp_sub = sub - 10 * delta_sub;
			subKey[index + i] = (abs(sub) >= abs(temp_sub) ? temp_sub : sub);
			ret = min(ret, 1 + setKey(index, subKey[index], subKey[index + 1], subKey[index + 2]));
		}
		for (int i = 0; i < 3; i++) {
			subKey[index + i] += press*delta;
			int sub = subKey[index + i];
			int delta_sub = (sub >= 0), temp_sub = sub - 10 * delta_sub;
			subKey[index + i] = (abs(sub) >= abs(temp_sub) ? temp_sub : sub);
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(cache, -1, sizeof(cache));
	cin >> n >> key >> nKey;
	for (int i = 0; i < n; i++){
		int sub = key[i] - nKey[i];
		int delta_sub = (sub >= 0), temp_sub = sub - 10 * delta_sub;
		subKey[i] = (abs(sub) >= abs(temp_sub) ? temp_sub : sub);
	}

	cout << setKey(0, subKey[0], subKey[1], subKey[2]) << endl;
	
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}