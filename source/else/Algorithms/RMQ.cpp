#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
struct RMQ {
	int n;
	vector<int> rangeValue;

	//���� Ʈ���� 1���� �迭�� 4 * n�� ũ��� ����
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeValue.resize(4 * n);
		init(array, 0, n - 1, 1);
	}

	//���ϴ� �ּ� ���� ����
	int func(int a, int b) {
		return min(a, b);
	}

	//�� ��帶�� �ּ�ġ�� �̸� �����ϴ� �ʱ�ȭ �۾�
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeValue[node] = array[left];
		int mid = (left + right) / 2;

		return func(init(array, left, mid, node * 2), init(array, mid + 1, right, node * 2 + 1));
	}

	//�ش� ����[left, right]�� �ּ�ġ�� ���ϴ� ���� �ذ� �۾�
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (nodeRight < left || right < nodeLeft) return INT_MAX;
		if (left <= nodeLeft && nodeRight <= right) return rangeValue[node];
		
		int mid = (nodeLeft + nodeRight) / 2;
		return func(query(left, right, node * 2, nodeLeft, mid), query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	//���ϴ� ����(index)�� ���� �����ϰ� �� ������ �ּҰ��� ��ȯ�Ѵ�.
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