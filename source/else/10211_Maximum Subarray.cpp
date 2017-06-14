#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;

int tc, n;

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	for (cin >> tc; tc > 0; tc--){
		cin >> n;
		int x[1005];
		for (int i = 0; i < n; i++) cin >> x[i];
		int ret = -987654321, val = 0;
		for (int i = 0; i < n; i++){
			val += x[i];
			if (val > ret) ret = val;
			else if (val < 0) val = 0;
		}
		cout << ret << endl; 
	}
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}