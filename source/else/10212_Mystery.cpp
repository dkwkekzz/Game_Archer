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
#include <ctime>
using namespace std;

const string output[2] = { "Yonsei", "Korea" };

int main(int argc, char** argv) {
	int a = 5;
	int b = 7;
	int c = (int(&a)+int(&b)) / 17;
	cout << output[c%2] << endl;
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}