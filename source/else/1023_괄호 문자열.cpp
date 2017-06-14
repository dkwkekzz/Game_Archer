#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;

const int64 INF = 987654321;
int64 n, k;
int64 cache[100][100];

int64 findString(int64 m, int64 c){
	if (c < 0) return 0;
	if (!m && !c) return 1;
	if (!m) return 0;

	int64 &ret = cache[m][c];
	if (ret != -1) return ret;

	return ret = findString(m - 1, c + 1) + findString(m - 1, c - 1);
}

int64 countSkip(int64 m, int64 c){
	int64 ret = pow<int64>(2, m);
	if (n&1 || c>m || c<0) return ret;
	return ret - findString(m, c);
}

string getString(int64 skip, int64 m, int64 c){
	if (!m && skip > 0) return "!";
	if (!m) return "";

	int64 s = countSkip(m - 1, c + 1);
	if (skip < s) return '(' + getString(skip, m - 1, c + 1);
	else{
		skip -= s;
		return ')' + getString(skip, m - 1, (c - 1 < 0 ? -INF : c - 1));
	}
}

bool check(int64 value){
	stack<int> s;
	for (int64 i = n - 1; i >= 0; i--){
		if ((static_cast<int64>(1) << i)&value){
			if (s.empty()) return 0;
			else s.pop();
		}
		else{
			s.push(0);
		}
	}
	return s.empty();
}

int64 solve(){
	int64 counter = 0;
	for (int64 i = 0; i < (static_cast<int64>(1) << n); i++){
		if (!check(i)) {
			if (counter == k) return i;
			counter++;
		}
	}
	return -1;
}

string printString(int64 value){
	if (value < 0) {
		return "-1";
	}
	string s("");
	for (int64 i = n - 1; i >= 0; i--){
		if ((static_cast<int64>(1) << i)&value){
			s += ')';
		}
		else s += '(';
	}
	return s;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(cache, -1, sizeof(cache));
	cin.sync_with_stdio(false);
	/*for (n = 1; n <= 30; n++){
		for (k = 0; k < pow(2, n); k++){
			string s1(getString(k, n, 0));
			if (s1.size() > n) s1 = "-1";
			string s2(printString(solve()));
			if (s1 != s2){
				cout << "error at: " << n << " " << k << endl;
			}
		}
	}*/
	cin >> n >> k;
	string ret(getString(k, n, 0));
	if (ret.size() > n) cout << -1 << endl;
	else cout << ret << endl;

	/*cin >> n >> k;
	cout << printString(solve()) << endl;*/

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}