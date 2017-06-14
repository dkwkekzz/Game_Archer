#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� scanf �Լ� �Ǵ� cin�� ����Ͽ� ǥ���Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž� �մϴ�. */
	//freopen("input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	int TC;
	int test_case;

	scanf_s("%d", &TC);	// cin ��� ����
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.

		int n;
		scanf_s("%d", &n);	// cin ��� ����
		
		vector<int> attendees(n);
		vector<int> attendees_sort(n);

		for (int i = 0; i < n; i++){
			int m;
			scanf_s("%d", &m);

			attendees[i] = m;
			attendees_sort[i] = m;
		}

		sort(attendees_sort.begin(), attendees_sort.end());

		int winner = 0;
		int best = 0;

		for (int i = 0; i < n; i++){
			best = max(best, attendees_sort[i] + n - i);
		}

		for (int i = 0; i < n; i++){
			if (attendees_sort[i] + n >= best) winner++;
		}

		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		printf("%d\n", winner);

	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}