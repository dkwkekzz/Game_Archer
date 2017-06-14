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

int n, k;
string num;

string solve(){
	stack<char> s;
	s.push(num[0]);
	int counter = k;
	for (int i = 1; i < n; i++){
		bool loop = false;
		while (!s.empty() && s.top() < num[i] && counter){
			loop = true;
			s.pop();
			counter--;
		}
		if (loop) s.push(num[i]);
		else s.push(num[i]);
	}
	while (counter-- > 0){
		s.pop();
	}
	string ret = "";
	while (!s.empty()){
		ret += s.top()
			;
		s.pop();
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin >> n >> k >> num;
	cout << solve() << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}