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

int n;
int room[1000][1000];

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.
		cin >> n;

		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++) {
				char c;
				cin >> c;
				room[i][j] = c - '0';
			}
		}

		int cnt = 0;
		int y = 0, x = 0, dy = 0, dx = 1;
		while (y >= 0 && x >= 0 && y < n && x < n){
			if (abs(room[y][x]) == 1) {
				swap(dx, dy); dy *= -1; dx *= -1; 
			}
			else if (abs(room[y][x]) == 2){
				swap(dx, dy);
			}
			if (room[y][x] > 0) {
				cnt++; room[y][x] *= -1;
			}
			y += dy; x += dx;
		}
		
		// �� �κп��� ������ ����Ͻʽÿ�.
		cout << "Case #" << test_case << "\n" << cnt << endl;
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}