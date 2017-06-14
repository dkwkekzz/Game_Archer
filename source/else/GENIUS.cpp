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

const int MAX_N = 50;
int n, k, m;
int length[MAX_N];
double T[MAX_N][MAX_N];

void init(){

}

void input(){

}

vector<double> solve(){
	double c[5][MAX_N];
	memset(c, 0, sizeof(c));
	c[0][0] = 1;
	for (int time = 1; time <= k; time++){
		for (int song = 0; song < n; song++){
			double &prob = c[time & 5][song];
			for (int last = 0; last < n; last++){
				prob += c[(time - length[last] + 1) % 5][last] * T[last][song];
			}
		}
	}
	vector<double> ret(n);
	for (int song = 0; song < n; song++){
		for (int start = k - length[song] + 1; start <= k; start++){
			ret[song] += c[start % 5][song];
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		init(); input();

	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}
