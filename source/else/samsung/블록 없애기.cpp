#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n;

pair<int, int> findLowest(const vector<pair<int, int> >& H, const vector<bool>& isDelete){
	for (int i = 0; i < n; i++){
		int first_index = H[i].first;
		if (!isDelete[first_index]) return H[i];
	}

	return pair<int, int>(-1, -1);
}

int solve(const vector<pair<int, int> >& H, vector<pair<int, int> >& deletePoint, vector<bool>& isDelete){
	int time = 0, re_block = n;

	while (re_block > 0){
		pair<int, int> lowest = findLowest(H, isDelete);
		int elapsedTime = lowest.second - time;

		for (int j = 0; j < elapsedTime; j++){
			time++;

			for (int i = 0; i < deletePoint.size(); i++){
				int index = deletePoint[i].first + (time - deletePoint[i].second);
				if (index < n){
					if (!isDelete[index]) {
						isDelete[index] = true; re_block--;
					}
				}

				index = deletePoint[i].first - (time - deletePoint[i].second);
				if (index >= 0){
					if (!isDelete[index]) {
						isDelete[index] = true; re_block--;
					}
				}
			}

			if (re_block <= 0) break;
		}

		deletePoint.push_back(pair<int, int>(lowest.first, time));
		if (!isDelete[lowest.first]) {
			isDelete[lowest.first] = true; re_block--;
		}
	}
	
	return time;
}

int compare(pair<int, int> i, pair<int, int> j){
	return i.second < j.second;
}

int main(int argc, char** argv) {
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� scanf �Լ� �Ǵ� cin�� ����Ͽ� ǥ���Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž� �մϴ�. */
	FILE *stream;

	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	cin.sync_with_stdio(false);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.
		cin >> n;
		vector<pair<int, int> > H(n);
		for (int i = 0; i < n; i++) {
			H[i].first = i; cin >> H[i].second;
		}
		sort(H.begin(), H.end(), compare);

		vector<bool> isDelete(n, 0);
		vector<pair<int, int> > deletePoint;
		deletePoint.push_back(pair<int, int>(-1, 0)); deletePoint.push_back(pair<int, int>(n, 0));

		printf("Case #%d\n", test_case);
		cout << solve(H, deletePoint, isDelete) << endl;
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}