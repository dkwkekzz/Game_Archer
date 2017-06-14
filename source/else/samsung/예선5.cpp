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

const int INF = 987654321;

int n, k;
int shoes[200][3];
int craftman[100][2];

void input(){
	cin >> n >> k;
	for (int i = 0; i < n; i++){
		cin >> shoes[i][0] >> shoes[i][1] >> shoes[i][2];
	}
	for (int i = 0; i < k; i++){
		cin >> craftman[i][0] >> craftman[i][1];
	}
}

bool operator<(pair<int, int> t, pair<int, int> u){
	return (t.first < u.first) || ((t.first == u.first) && (shoes[t.second][1] > shoes[u.second][1]));
}


int solve(){
	priority_queue<pair<int, int> > factory;
	for (int time = 0; time < 100; time++){
		/*for (int si = 0; si < n; si++){
			if (shoes[si][0] == time){
				for (int item = 0; item < shoes[si][2]; item++){
					factory.push(make_pair(-((shoes[si][1] - shoes[si][0]) - shoes[si][2]), si));
				}
			}
		}*/
		while (factory.size() > 0){
			pair<int, int> temp = factory.top();
			factory.pop();
			shoes[temp.second][2]++;
		}

		for (int si = 0; si < n; si++){
			if ((time >= shoes[si][1]) && shoes[si][2] > 0) return 0;
			if (shoes[si][0] <= time && shoes[si][1] > time && shoes[si][2] > 0){
				int priority = (shoes[si][1] - time) - shoes[si][2];
				factory.push(make_pair(-priority, si));
				shoes[si][2]--;
			}
		}

		/*vector<pair<int, int> > temp;
		int crafting = INF;
		for (int ci = 0; ci < k; ci++){
			if (craftman[ci][0] <= time && craftman[ci][1] > time){
				if (factory.size() > 0) {
					while (crafting == factory.top().second){
						temp.push_back(factory.top());
						factory.pop();
						if(factory.size() == 0){
							crafting = -INF; break;
						}
					}
					if (crafting == -INF) break;
					crafting = factory.top().second;
					factory.pop();
				}
			}
		}
		for (int i = 0; i < temp.size(); i++) factory.push(temp[i]);*/
		for (int ci = 0; ci < k; ci++){
			if (craftman[ci][0] <= time && craftman[ci][1] > time){
				if (factory.size() > 0) {
					factory.pop();
				}
			}
		}
	}

	return factory.size() > 0 ? 0 : 1;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);

	int TC;

	cin >> TC;
	for (int test_case = 1; test_case <= TC; test_case++) {
		memset(shoes, -1, sizeof(shoes));
		memset(craftman, -1, sizeof(craftman));
		input();

		cout << "Case #" << test_case << "\n" << solve() << endl;
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}