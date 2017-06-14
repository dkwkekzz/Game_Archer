#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int n;

unsigned int calcXOR(unsigned int a, unsigned int b){
	return a ^ b;
}

int main(int argc, char** argv) {
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� scanf �Լ� �Ǵ� cin�� ����Ͽ� ǥ���Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž� �մϴ�. */
	//freopen("input.txt", "r", stdin);

	//setbuf_s(stdout, NULL);

	int TC;
	int test_case;

	scanf_s("%d", &TC);	// cin ��� ����
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.

		scanf_s("%d", &n);

		map<unsigned int, bool> nBox;

		for (int i = 0; i < n; i++){
			unsigned int m;
			scanf_s("%u", &m);

			//true: even   false: odd
			if (nBox[m] == NULL || nBox[m] == false) nBox[m] = true;
			else nBox[m] = false;
		}

		unsigned int head = 0;
		for (map<unsigned int, bool>::iterator it = nBox.begin(); it != nBox.end(); ++it){
			if (it->second) head = calcXOR(head, it->first);
		}

		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		printf("%u\n", head);

	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}