#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
struct RMQ {
	int n;
	vector<int> rangeValue;

	//구간 트리를 1차원 배열로 4 * n의 크기로 생성
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeValue.resize(4 * n);
		init(array, 0, n - 1, 1);
	}

	//원하는 최소 단위 질의
	int func(int a, int b) {
		return min(a, b);
	}

	//각 노드마다 최소치를 미리 저장하는 초기화 작업
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeValue[node] = array[left];
		int mid = (left + right) / 2;

		return func(init(array, left, mid, node * 2), init(array, mid + 1, right, node * 2 + 1));
	}

	//해당 구간[left, right]의 최소치를 구하는 질의 해결 작업
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (nodeRight < left || right < nodeLeft) return INT_MAX;
		if (left <= nodeLeft && nodeRight <= right) return rangeValue[node];
		
		int mid = (nodeLeft + nodeRight) / 2;
		return func(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	//원하는 원소(index)의 값을 갱신하고 그 원소의 최소값을 반환한다.
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		if (nodeRight < index || index < nodeLeft) return INT_MAX;
		if (nodeLeft == nodeRight) return rangeValue[node] = newValue;

		int mid = (nodeLeft + nodeRight) / 2;
		return func(update(index, newValue, node * 2, nodeLeft, mid), update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
};