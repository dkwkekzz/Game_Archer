// 아래 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하셔도 됩니다.
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
	/* 아래 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	앞으로 표준 입력(키보드) 대신 input.txt 파일로 부터 읽어오겠다는 의미의 코드입니다.
	만약 본인의 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면,
	그 아래에서 scanf 함수 또는 cin을 사용하여 표준입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	또한, 본인 PC에서 freopen 함수를 사용하지 않고 표준입력을 사용하여 테스트하셔도 무방합니다.
	단, Codeground 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석(//) 처리 하셔야 합니다. */
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

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}