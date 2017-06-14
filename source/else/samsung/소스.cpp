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
	/* 아래 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	앞으로 표준 입력(키보드) 대신 input.txt 파일로 부터 읽어오겠다는 의미의 코드입니다.
	만약 본인의 PC 에서 테스트 할 때는, 입력값을 input.txt에 저장한 후 freopen 함수를 사용하면,
	그 아래에서 cin 을 사용하여 표준 입력 대신 input.txt 파일로 부터 입력값을 읽어 올 수 있습니다.
	따라서 본인의 PC 에서 테스트 할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 됩니다.
	단, 이 시스템에서 "제출하기" 할 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다. */

	init_fac();

	scanf("%d", &T);	//Codeground 시스템에서는 C++ 에서도 scanf 사용을 권장합니다.
	for (test_case = 1; test_case <= T; ++test_case) {
		//	이 부분에서 알고리즘 프로그램을 작성하십시오.

		input();
		long long ans = process(k + 1);

		//	이 부분에서 정답을 출력하십시오. Codeground 시스템에서는 C++ 에서도 printf 사용을 권장합니다. 
		printf("Case #%d\n", test_case);
		printf("%lld\n", ans);
	}

	return 0;	//	정상종료 시 반드시 0을 리턴해야 합니다.
}
