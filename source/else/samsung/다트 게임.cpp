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

		for (int i = 0; i < 5; i++){
			scanf_s("%d", &radius[i]);

			radius[i] *= radius[i];
		}

		int n;
		int sum = 0;

		scanf_s("%d", &n);	// cin ��� ����
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

		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		printf("%d\n", sum);
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}


