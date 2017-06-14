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
typedef unsigned long long uint64;

const int MAX_N = 1000001, MAX_COUNT = 1000000000 * 2;
unsigned char sieve[(MAX_N + 7) / 8];
int n;

void init(){
	memset(sieve, (1 << 8) - 1, sizeof(sieve));
}

void input(vector<int>& lottery){
	cin >> n;
	lottery = vector<int>(n + 1, -1);
	for (int i = 1; i <= n; i++) cin >> lottery[i];
}

void preCalc(){

}

int isSame(int n){
	return sieve[n >> 3] & (1 << (n & 7));
}

void setComposite(int n){
	sieve[n >> 3] &= ~(1 << (n & 7));
}

int solve(const vector<int>& lottery){
	vector<bool> visited(n + 1, 0);
	vector<int> cycle;
	for (int i = 1; i <= n; i++){
		int here = i, cycleSize = 0;
		if (here == lottery[here]) return -1;
		for (int j = 0; j < MAX_N; j++){
			if (visited[here]) break;
			visited[here] = 1;
			here = lottery[here];
			cycleSize++;
			if (i == here){
				cycle.push_back(cycleSize);
				break;
			}
		}
	}
	sort(cycle.begin(), cycle.end());

	setComposite(0); setComposite(1);
	for (int i = 0; i < cycle.size(); i++){
		int value = cycle[i];
		if (isSame(value)) {
			for (int j = value; j <= n; j += value)
				setComposite(j);
		}
	}

	for (int i = 2; i <= n; i++){
		if (isSame(i)) return i;
	}

	return -1;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	vector<int> lottery;
	init(); input(lottery); preCalc();
	cout << solve(lottery) << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}