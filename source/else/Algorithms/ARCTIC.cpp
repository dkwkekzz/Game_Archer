#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

int n;
double location[100][2];
double dist[100][100];
double bestDist[100];

double setDist(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for (int there = 0; there < n; there++) {
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
		}
	}
	return seen == n;
}

double opimize() {
	double lo = 0.0, hi = 1416.0;
	for (int i = 0; i < 100; i++) {
		double mid = (lo + hi) / 2;
		if (decision(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

bool decision(double d) {
	vector<bool> visited(n, false);
	for (int here = 0; here < n; here++)
	for (int i = here + 1; i < n; i++) {
		if (visited[i] == true || bestDist[i] > d) return false;
	}
	return true;
}


int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> location[i][0] >> location[i][1];
	}
}