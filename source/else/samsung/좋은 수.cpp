// �Ʒ� �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����ϼŵ� �˴ϴ�.
#include <cstdio>
#include <iostream>
using namespace std;

const int COM = 600000;

int cache[1200001];

int A[5001];

int n;

int first;

void calcInit(){
	first = A[0];

	for (int i = 0; i < n; i++){
		A[i] -= first;
		A[i] += COM;
	}
}

bool searchOtherSum(int selectedNum, int index){
	for (int searchSum = index - 1; searchSum > 0; searchSum--){
		int sNum = A[searchSum], nNum = selectedNum - sNum + COM;

		int a = cache[sNum], b = cache[nNum];

		if (a != -1 && b != -1 && a + b <= 3){
			cache[selectedNum] = a + b;

			return true;
		}
	}

	return false;
}

int countGoodNumber(){
	int ret = 0;

	for (int i = 1; i < n; i++){
		int nNum = A[i];
		int selectedNum = nNum - 2 * first;

		if (cache[selectedNum] != -1) ret++;
		else if(searchOtherSum(selectedNum, i)) ret++;

		int &oneNum = cache[nNum] = 1;
		int doubleCom = (nNum - COM) * 2 + COM;
		int &doubleNum = ((cache[doubleCom] == -1 || cache[doubleCom] == 3) ? cache[doubleCom] = 2 : cache[doubleCom]);
		int tripleCom = (nNum - COM) * 3 + COM;
		int &tripleNum = (cache[tripleCom] == -1 ? cache[tripleCom] = 3 : cache[tripleCom]);
	}

	return ret;
}

int main(int argc, char** argv) {
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� scanf �Լ� �Ǵ� cin�� ����Ͽ� ǥ���Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž� �մϴ�. */
	FILE *input;

	freopen_s(&input, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);
	cin.sync_with_stdio(false);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		memset(cache, -1, sizeof(cache));
		cache[COM] = 0;

		cin >> n;

		for (int i = 0; i < n; i++){
			cin >> A[i];
		}

		calcInit();

		cout << countGoodNumber() << endl;
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}