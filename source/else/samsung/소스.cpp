#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define K 2005
#define N 100005
#define MOD 1000000007

using namespace std;

int n, m, k;
long long fac[N * 2], facinv[N * 2];

struct data
{
	int y, x;
	long long d;
}a[K];

bool compare(data x, data y)
{
	return (x.y < y.y || x.y == y.y && x.x < y.x);
}

void input()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d %d", &a[i].y, &a[i].x);
		a[i].d = -1;
	}
	a[k + 1].y = n;
	a[k + 1].x = m;
	a[k + 1].d = -1;
	sort(a + 1, a + k + 1, compare);
}

long long get_count(int y, int x)
{
	return (((fac[(y - 1) + (x - 1)] * facinv[y - 1]) % MOD)*facinv[x - 1]) % MOD;
}

long long process(int cur)
{
	int cnt = 0;
	long long tmp = 0;
	int y = a[cur].y;
	int x = a[cur].x;

	long long &ret = a[cur].d;
	if (ret != -1) return ret;

	for (int i = 1; i <= k; i++) {
		if (a[i].x > x) continue;
		if (a[i].y == y && a[i].x == x) break;
		tmp = (tmp + (process(i)*get_count(y - a[i].y + 1, x - a[i].x + 1))) % MOD;
	}

	return ret = (get_count(y, x) - tmp + MOD) % MOD;
}

long long get_exp(long long x, long long y)
{
	if (y == 0) return 1;
	long long ret = get_exp(x, y >> 1);
	ret = (ret*ret) % MOD;
	if (y & 1) ret = (ret*x) % MOD;
	return ret;
}

void init_fac()
{
	fac[0] = facinv[0] = 1;
	for (int i = 1; i <= 200000; i++) {
		fac[i] = (fac[i - 1] * i) % MOD;
		facinv[i] = get_exp(fac[i], MOD - 2);
	}
}

int main(int argc, char** argv) {
	int T;
	int test_case;
	/* �Ʒ� freopen �Լ��� input.txt �� read only �������� �� ��,
	������ ǥ�� �Է�(Ű����) ��� input.txt ���Ϸ� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	���� ������ PC ���� �׽�Ʈ �� ����, �Է°��� input.txt�� ������ �� freopen �Լ��� ����ϸ�,
	�� �Ʒ����� cin �� ����Ͽ� ǥ�� �Է� ��� input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
	���� ������ PC ���� �׽�Ʈ �� ������ �Ʒ� �ּ��� ����� �� �Լ��� ����ϼŵ� �˴ϴ�.
	��, �� �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ� ó�� �ϼž� �մϴ�. */

	init_fac();

	scanf("%d", &T);	//Codeground �ý��ۿ����� C++ ������ scanf ����� �����մϴ�.
	for (test_case = 1; test_case <= T; ++test_case) {
		//	�� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�.

		input();
		long long ans = process(k + 1);

		//	�� �κп��� ������ ����Ͻʽÿ�. Codeground �ý��ۿ����� C++ ������ printf ����� �����մϴ�. 
		printf("Case #%d\n", test_case);
		printf("%lld\n", ans);
	}

	return 0;	//	�������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}
