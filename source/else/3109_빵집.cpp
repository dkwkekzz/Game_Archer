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
const int MAX_R = 10000 + 5, MAX_C = 500 + 5;
int r, c;
string land[MAX_R];
vector<int> iter;

bool search(int y, int x){
	if (x == c - 1) return true;
	
	while (iter[x] + 1 <= y + 1){
		iter[x]++;
		if (iter[x] >= y - 1 && land[iter[x]][x] == '.'){
			if(search(iter[x], x + 1)) return true;
		}
	}
	return false;
}

int solve(){
	int ret = 0;
	for (int y = 1; y <= r; y++){
		if (search(y, 1)) ret++;
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;

	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> r >> c;
	iter = vector<int>(c, 0);
	land[0] = land[r + 1] = string(c, 'x');
	for (int i = 1; i <= r; i++) cin >> land[i];
	cout << solve() << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}