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

int n, amount;
int prices[10];

void solve(){
	vector<pair<int, int> > numbers;
	for (int i = 0; i < n; i++) {
		while (!numbers.empty() && numbers.back().second >= prices[i]) numbers.pop_back();
		if (prices[i]) numbers.push_back(make_pair(i, prices[i]));
	}
	vector<int> ret;
	while (amount > 0){
		int cand = numbers[0].first;
		if (ret.empty() && !cand) cand = numbers[1].first;
		if (amount - prices[cand] < 0) break;
		ret.push_back(cand);
		amount -= prices[cand];
	}
	for (int i = 0; i < ret.size(); i++){
		int cur = ret[i];
		for (int j = 0; j + 1 < numbers.size(); j++){
			if (numbers[j].first != cur) continue;
			int next = numbers[j + 1].first;
			int price = prices[next] - prices[cur];
			if (amount - price >= 0){
				amount -= price;
				cur = next;
			}
			else break;
		}
		printf("%d", cur);
	}
	if (ret.empty()) printf("0");
	printf("\n");
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	while (scanf_s("%d", &n) >= 0){
		memset(prices, 0, sizeof(prices));
		for (int i = 0; i < n; i++) scanf_s("%d", &prices[i]);
		scanf_s("%d", &amount);
		solve();
	}
	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}