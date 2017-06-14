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

	memset(factorial_cache, -1, sizeof(factorial_cache));

	precalc_factorial(200001);

	int TC;
	int test_case;

	cin >> TC;
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.
		cin >> n >> m >> k;
		// ��ֹ��� ���� ��, ��ü ����� ��
		unsigned long long sum = bino(n + m - 2, n - 1);
		// ��ֹ� �Է�
		for (int i = 0; i < k; i++){
			unsigned long long y, x;

			cin >> y >> x;
			K[i] = (checkInBoard(y, x) ? y * 100000 + x : 0);
		}
		// ��ֹ��� y, x������ ���ĵǾ� �ִ�.
		sort(K, K + k);
		// ��ֹ��� �������� ����� ���� ����.
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

		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		printf("%lld\n", sum);
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}