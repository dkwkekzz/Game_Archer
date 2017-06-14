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
typedef long long int64;

const int INF = 987654321, MAX_N = 1000;
int n, a, b;
int balloons[MAX_N + 5];
pair<int, int> dist[MAX_N + 5];

int solve(){
	int ret = 0;
	priority_queue<pair<int, int> > pq;
	for (int i = 0; i < n; i++)
		pq.push(make_pair(-min(dist[i].first, dist[i].second), i));
	for (int i = 0; i < n; i++){
		pair<int, int> thing = pq.top();
		pq.pop();
		int j = thing.second, balloon = balloons[j], aD = dist[j].first, bD = dist[j].second;
		if (aD < bD){
			if (a < balloon) {
				ret += aD * a;
				pq.push(make_pair(-bD, j));
				balloons[j] = balloon - a;
				i--;
			}
			else{
				a -= balloon;
				ret += aD*balloon;
			}
		}
		else{
			if (b < balloon) {
				ret += bD * b;
				pq.push(make_pair(-aD, j));
				balloons[j] = balloon - b;
				i--;
			}
			else{
				b -= balloon;
				ret += bD*balloon;
			}
		}
	}

	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	while (1){
		scanf_s("%d %d %d", &n, &a, &b);
		if (n == 0 && a == 0 && b == 0) break;
		for (int i = 0; i < n; i++){
			scanf_s("%d %d %d", &balloons[i], &dist[i].first, &dist[i].second);
		}
		printf("%d\n", solve());
	}


	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}