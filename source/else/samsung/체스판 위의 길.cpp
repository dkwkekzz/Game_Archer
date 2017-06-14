#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

const unsigned long long MOD = 1000000007;

unsigned long long factorial_cache[200001];

int n, m, k;

unsigned long long K[2000];

class m_pair{
public:
	int a;
	int b;

	m_pair(int _a, int _b) : a(_a), b(_b) { };
	void set(int _a, int _b){
		a = _a; b = _b;
	}
};

m_pair mul(const m_pair& m_a, int m){
	m_pair ret(m_a.a * m, m_a.b * m);

	return ret;
}

m_pair sub(const m_pair& m_a, const m_pair& m_b){
	m_pair ret(m_a.a - m_b.a, m_a.b - m_b.b);

	return ret;
}

unsigned long long modula_inverse(int a, int b){
	if (b == 1) return 1;

	int r, q, sub_q, ret;

	m_pair ret_m(1, 0), q_m(0, 1), r_m(0, 0);

	q = a; r = b;
	while (r != 1){
		ret = q; q = r; sub_q = ret / q;

		r = ret - q * sub_q;

		r_m = sub(ret_m, mul(q_m, sub_q));
		ret_m = q_m; q_m = r_m;
	}

	return r_m.b >= 0 ? r_m.b : MOD + r_m.b;
}

unsigned long long bino(unsigned long long n, unsigned long long r){
	if (r == 0 || n == r) return 1;

	return factorial_cache[n] * modula_inverse(MOD, factorial_cache[r] * factorial_cache[n - r] % MOD) % MOD;
}

void precalc_factorial(int n){
	factorial_cache[0] = 1;

	for (int i = 1; i <= n; i++){
		factorial_cache[i] = (factorial_cache[i - 1] * i) % MOD;
	}
}

bool checkInBoard(unsigned long long y, unsigned long long x){
	return (y <= n && x <= m) && (y > 0 && x > 0);
}

bool checkInScope(int index, unsigned long long y, unsigned long long x){
	unsigned long long cy = K[index] / 100000, cx = K[index] % 100000;
	if (cx == 0) {
		cy--; cx = 100000;
	}

	return (y >= cy && x >= cx);
}

unsigned long long calcDistanceValue(int index, unsigned long long y, unsigned long long x){
	unsigned long long cy = K[index] / 100000, cx = K[index] % 100000;
	if (cx == 0) {
		cy--; cx = 100000;
	}

	unsigned long long ny = y - cy, nx = x - cx;

	return bino(ny + nx, ny) % MOD;
}

int main(int argc, char** argv) {
	/* 아래 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	앞으로 표준 입력(키보드) 대신 input.txt 파일로 부터 읽어오겠다는 의미의 코드입니다.
	만약 본인의 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면,
	그 아래에서 scanf 함수 또는 cin을 사용하여 표준입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	또한, 본인 PC에서 freopen 함수를 사용하지 않고 표준입력을 사용하여 테스트하셔도 무방합니다.
	단, Codeground 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석(//) 처리 하셔야 합니다. */
	FILE *stream;
	
	freopen_s(&stream, "input.txt", "r", stdin);

	//setbuf(stdout, NULL);

	cin.sync_with_stdio(false);

	memset(factorial_cache, -1, sizeof(factorial_cache));

	precalc_factorial(200001);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// 이 부분에서 알고리즘 프로그램을 작성하십시오.
		cin >> n >> m >> k;
		// 장애물이 없을 시, 전체 경우의 수
		unsigned long long sum = bino(n + m - 2, n - 1);
		// 장애물 입력
		for (int i = 0; i < k; i++){
			unsigned long long y, x;

			cin >> y >> x;
			K[i] = (checkInBoard(y, x) ? y * 100000 + x : 0);
		}
		// 장애물은 y, x순으로 정렬되어 있다.
		sort(K, K + k);
		// 장애물을 지나가는 경우의 수를 뺀다.
		unsigned long long obstacleArray[2000];

		for (int i = 0; i < k; i++){
			if (K[i] == 0) continue;

			unsigned long long y = K[i] / 100000, x = K[i] % 100000;
			if (x == 0) {
				y--; x = 100000;
			}

			obstacleArray[i] = 0;

			for (int j = 0; j < i; j++){
				if (K[j] == 0) continue;
				
				if (checkInScope(j, y, x)) {
					obstacleArray[i] = (obstacleArray[i] + obstacleArray[j] * calcDistanceValue(j, y, x)) % MOD;
				}
			}
			obstacleArray[i] = (bino(y + x - 2, y - 1) - obstacleArray[i] + MOD) % MOD;
			
			unsigned long long obstacleSub = (bino((n - y) + (m - x), n - y) * obstacleArray[i]) % MOD;

			sum = (sum - obstacleSub + MOD) % MOD;
		}

		// 이 부분에서 정답을 출력하십시오.
		printf("Case #%d\n", test_case);	// cout 사용 가능
		printf("%lld\n", sum);
	}

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}