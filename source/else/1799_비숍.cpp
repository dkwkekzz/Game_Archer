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
const int MAX_N = 10 + 5, INF = 987654321;
int n;
int best;
int board[MAX_N][MAX_N];

bool canSet(const vector<pair<int, int> >& group, int my, int mx){
	if (!board[my][mx]) return false;
	for (int i = 0; i < group.size(); i++){
		int ny = group[i].first, nx = group[i].second;
		if (abs(ny - my) == abs(nx - mx)) return false;
	}
	return true;
}

void setBishop(vector<pair<int, int> >& group, int index){
	if (index > 2 * n - 2) {
		best = max(best, static_cast<int>(group.size()));
		return;
	}
	int y = max(0, index - n + 1), x = min(n - 1, index);
	bool selected = false;
	for (int i = 0; i <= min(index, (2*n - 2) - index); i++){
		if (canSet(group, y, x)){
			selected = true;
			group.push_back(make_pair(y, x));
			setBishop(group, index + 1);
			group.pop_back();
		}
		y++; x--;
	}
	if(!selected) setBishop(group, index + 1);
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	scanf_s("%d", &n);
	for (int y = 0; y < n; y++)
	for (int x = 0; x < n; x++){
		scanf_s("%d", &board[y][x]);
	}
	vector<pair<int, int> > group;
	setBishop(group, 0);
	cout << best << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}