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

const int MAX_N = 101, INF = 987654321;

int n;
int line[MAX_N][4];

void input(){
	memset(line, -1, sizeof(line));
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++) scanf_s("%d %d %d %d", &line[i][0], &line[i][1], &line[i][2], &line[i][3]);
}

int getInSide(int a){
	vector<int> vertexStack;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			vertexStack.push_back(abs(line[i][a] + line[j][a]));
			vertexStack.push_back(abs(line[i][a] + line[j][a + 2]));
			vertexStack.push_back(abs(line[i][a + 2] + line[j][a]));
			vertexStack.push_back(abs(line[i][a + 2] + line[j][a + 2]));
		}
	}
	int ret = INF;
	for (int i = 0; i < vertexStack.size(); i++){
		int value = 0, point = vertexStack[i];
		for (int j = 0; j < n; j++){
			value = max(value, min(abs(point - line[j][a] * 2), abs(point - line[j][a + 2] * 2)));
		}
		ret = min(ret, value);
	}

	return ret;
}

double solve(){
	return static_cast<double>(max(getInSide(0), getInSide(1))) / 2.0f;
}

int main(int argc, char** argv) {
	FILE *stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	int TC; scanf_s("%d", &TC);
	for (int test_case = 1; test_case <= TC; test_case++) {
		input();

		double ret = solve();
		int upRet = (int)ceil(ret);
		int doRet = (int)floor(ret);
		if (doRet != ret && upRet != ret)
			printf("Case #%d\n%.1f\n", test_case, ret);
		else
			printf("Case #%d\n%d\n", test_case, (int)ret);
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}