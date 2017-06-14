#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int dist[10][10];

int shortestPath(vector<int> &Path, vector<int> &visited, int length, int rest) {
	if (rest == 0) return length + dist[Path.back()][Path[0]];

	int ret = 9999;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			Path.push_back(i);
			visited[i] = 1;
			ret = min(ret, shortestPath(Path, visited, length + dist[Path.back()][i], i, rest - 1));
			Path.pop_back();
			visited[i] = 0;
		}
	}
	return ret;
}