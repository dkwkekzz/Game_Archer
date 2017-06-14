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

const int MAX_NM = 1000000000, MAX_K = 5000;
int n, m, k;
int rec[MAX_K][4];

struct rectangle{
	int num;
	vector<rectangle> child;
	rectangle(int n) : num(n) {};
};

void init(){
	memset(rec, -1, sizeof(rec));
}

void input(){
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) 
		cin >> rec[i][0] >> rec[i][1] >> rec[i][2] >> rec[i][3];
}

void preCalc(){

}

int solve(){
	int ret = 1; //x1, y1, x2, y2
	for (int i = 0; i < k; i++){
		for(int j = 0; j < k; j++){
			if (i == j) continue;
			if (rec[i][0] <= rec[j][0] && rec[i][2] >= rec[j][2]
				&& rec[i][1] <= rec[j][1] && rec[i][3] >= rec[j][3])
				counter++;
		}
		ret = max(ret, counter);
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC; cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		init(); input(); preCalc();

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}