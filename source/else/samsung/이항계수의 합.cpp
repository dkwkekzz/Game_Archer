#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;

const int MOD = 1000000007;

unsigned long long factorial_cache[2000002];

int n, m;

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

int modula_inverse(int a, int b){
	if (a < b) modula_inverse(b, a);
	
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

int bino(int n, int r){
	return factorial_cache[n] * modula_inverse(MOD, factorial_cache[r] * factorial_cache[n - r] % MOD) % MOD;
}

void precalc_factorial(int n){
	factorial_cache[0] = 1;

	for (int i = 1; i <= n; i++){
		factorial_cache[i] = (factorial_cache[i - 1] * i) % MOD;
	}
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

	memset(factorial_cache, -1, sizeof(factorial_cache));

	precalc_factorial(2000001);

	int TC;
	int test_case;

	scanf_s("%d", &TC);	// cin ��� ����
	for (test_case = 1; test_case <= TC; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.

		scanf_s("%d %d", &n, &m);

		int sum = bino(n + m + 2, n + 1) - 1;
		
		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("Case #%d\n", test_case);	// cout ��� ����
		printf("%d\n", sum);
	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}