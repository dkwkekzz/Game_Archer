#include <iostream>
#include <queue>
using namespace std;

int n;
int A[200000];

void input(int a, int b) {
	A[0] = 1983;
	for (int i = 1; i < n; i++)
		A[i] = (A[i - 1] * (long long)a + b) % 20090711;
	for (int i = 1; i < n; i += 2)
		A[i] *= -1;
}

int median(priority_queue<int>& max, priority_queue<int>& min) {
	int ret = 0;

	for (int i = 0; i < n; i++) {
		if(A[i] > 0) max.push(A[i]); 
		else min.push(A[i]);

		if (!min.empty() && (max.top() > min.top() * -1)) {
			int max_e = max.top();
			int min_e = min.top();
			max.pop();
			min.pop();
			max.push(min_e * -1);
			min.push(max_e * -1);
		}
		ret += max.top();
		ret %= 20090711;
	}
	return ret;
}

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b) : a(_a), b(_b), seed(1983) { }
	int next() {
		int ret = seed;
		seed = (seed * (long long)a + b) % 20090711;
		return ret;
	}
};

struct compare
{
	bool operator()(const int& l, const int& r)
	{
		return l > r;
	}
};

int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int> > maxHeap;
	priority_queue<int, vector<int>, compare > minHeap;
	int ret = 0;

	for (int cnt = 1; cnt <= n; cnt++) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		if (!maxHeap.empty() && !minHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(); int b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main() {
	int a, b;
	cin >> n >> a >> b;
	//input(a, b);

	priority_queue<int> maxHeap, minHeap;

	//cout << median(maxHeap, minHeap) << endl;
	cout << runningMedian(n, RNG(a, b));

}