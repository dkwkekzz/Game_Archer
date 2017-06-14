#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char** argv) {
	/* 아래 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	앞으로 표준 입력(키보드) 대신 input.txt 파일로 부터 읽어오겠다는 의미의 코드입니다.
	만약 본인의 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면,
	그 아래에서 scanf 함수 또는 cin을 사용하여 표준입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	또한, 본인 PC에서 freopen 함수를 사용하지 않고 표준입력을 사용하여 테스트하셔도 무방합니다.
	단, Codeground 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석(//) 처리 하셔야 합니다. */
	//freopen("input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	int TC;
	int test_case;

	scanf_s("%d", &TC);	// cin 사용 가능
	for (test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오.

		int n;
		scanf_s("%d", &n);	// cin 사용 가능
		
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

		// 이 부분에서 정답을 출력하십시오.
		printf("Case #%d\n", test_case);	// cout 사용 가능
		printf("%d\n", winner);

	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}