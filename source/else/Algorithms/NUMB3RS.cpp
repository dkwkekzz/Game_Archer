#include <iostream>
#include <algorithm>
using namespace std;

int n, d, p, t;
bool road[50][50];
double deg[50];
int q[50];
double cashe[100][50][50], cashe2[51][101];

double move(int day, int location, int q) {
	if (day == 0) {
		if (location == q) return 1.0;
		else return 0.0;
	}
	
	double &ret = cashe[day][location][q];
	if (ret > -0.5) return ret;
	
	ret = 0.0;
	for (int next = 0; next < n; next++) {
		if (location != next && road[location][next]) ret += move(day - 1, next, q) * 1.0 / deg[location];
	}
	return ret;
}

double search3(int here, int day) { //거꾸로 탐색하기
	if (day == 0) return (here == p ? 1.0 : 0.0);

	double &ret = cashe2[here][day];
	if (ret > -0.5) return ret;

	ret = 0.0;
	for (int there = 0; there < n; there++)
		if (road[here][day]) ret += search3(there, day - 1) / deg[there];
	return ret;
}

int main() {
	memset(cashe, -1, sizeof(cashe));
	memset(deg, 0, sizeof(deg));
	cin >> n >> d >> p;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) {
			cin >> road[i][j];
			if (road[i][j] == 1) deg[i] += 1.0;
		}
			
	cin >> t;
	for (int i = 0; i < t; i++)
		cin >> q[i];

	for (int i = 0; i < t; i++) {
		double ret = move(d, p, q[i]);
		cout << ret << " ";
	}
}