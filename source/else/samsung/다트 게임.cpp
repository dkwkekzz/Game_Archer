#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define PI 3.1415

const double range[6][2] = {
	{ tan(0 / 180.f * PI), tan(9 / 180.f * PI) }, { tan(9 / 180.f * PI), tan(27 / 180.f * PI) }, { tan(27 / 180.f * PI), tan(45 / 180.f * PI) },
	{ tan(45 / 180.f * PI), tan(63 / 180.f * PI) }, { tan(63 / 180.f * PI), tan(81 / 180.f * PI) }, { tan(81 / 180.f * PI), tan(90 / 180.f * PI) }
};

const int scores2[4][6] = {
	{ 6, 13, 4, 18, 1, 20 },
	{ 11, 14, 9, 12, 5, 20 },
	{ 11, 8, 16, 7, 19, 3 },
	{ 6, 10, 15, 2, 17, 3 }
};

const int scores[5] = { 50, 1, 3, 1, 2 };

int radius[5];

int judgeDist(int x, int y){
	int dist = x * x + y * y;

	for (int j = 0; j < 5; j++){
		if (radius[j] > dist) return scores[j];
	}

	return 0;
}

int judgeSlope(int x, int y){
	double slope;
	int index = 0;
	
	if (x >= 0 && y >= 0){
		if (x == 0) return 20;
		if (y == 0) return 6;

		index = 0;
	}
	else if (x <= 0 && y >= 0){
		if (x == 0) return 20;
		if (y == 0) return 11;

		index = 1;
	}
	else if (x <= 0 && y <= 0){
		if (x == 0) return 3;
		if (y == 0) return 11;

		index = 2;
	}
	else if (x >= 0 && y <= 0){
		if (x == 0) return 3;
		if (y == 0) return 6;

		index = 3;
	}

	slope = static_cast<double>(y) / static_cast<double>(x);
	slope = abs(slope);

	for (int i = 0; i < 6; i++){
		if (slope > range[i][0] && slope < range[i][1]) return scores2[index][i];
	}

	return 0;
}

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

		for (int i = 0; i < 5; i++){
			scanf_s("%d", &radius[i]);

			radius[i] *= radius[i];
		}

		int n;
		int sum = 0;

		scanf_s("%d", &n);	// cin 사용 가능
		for (int i = 0; i < n; i++){
			int x, y;
			
			scanf_s("%d %d", &x, &y);
			
			int score = 0, mul = 1;

			mul = judgeDist(x, y);
			if (mul == 50 || mul == 0) {
				sum += mul; continue;
			}

			score = judgeSlope(x, y);

			sum += mul * score;
		}

		// 이 부분에서 정답을 출력하십시오.
		printf("Case #%d\n", test_case);	// cout 사용 가능
		printf("%d\n", sum);
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}


