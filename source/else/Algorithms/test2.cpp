#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#include <Winbase.h>
#define MAX 987654321
#define threadMAX 987
using namespace std;

int n, m, sqrtn;
unsigned char sieve[MAX / 8];
int sharingI = -1;
int threadPartial;
int threadPartialIndex[threadMAX];

inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}

inline void setPrime(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7));
}

unsigned __stdcall ThreadFunc(void* threadPartialIndex)
{
	int i = ++sharingI;
	while (i <= sqrtn) {
		if (isPrime(i)) {
			for (int j = i * i; j <= n; j += i)
				setPrime(j);
		}
		i++;
	}
	_endthreadex(0);
	return 0;
}

/*unsigned __stdcall ThreadFunc(void* threadParameter)
{
	printf("%d\n", threadParameter);
	for (int i = (int)threadParameter * threadPartial; i <= ((int)threadParameter + 1) * threadPartial; i++)
		if (isPrime(i))
			for (int j = i * i; j <= n; j += i)
				setPrime(j);
	_endthreadex(0);
	return 0;
}*/

void eratosthenes() {
	memset(sieve, 255, sizeof(sieve));
	setPrime(0), setPrime(1);
	sqrtn = (int)sqrt(n);
	threadPartial = sqrtn / m + 1;
	HANDLE hThread[threadMAX];
	unsigned threadID[threadMAX];

	/*LARGE_INTEGER start, end, f;
	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&start);*/
	for (int i = 0; i < m; i++) {
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunc, 0, 0, &threadID[i]);
	}

	WaitForMultipleObjects(m, hThread, true, INFINITE);
	for (int i = 0; i < m; i++) {
		CloseHandle(hThread[i]);
	}

	/*QueryPerformanceCounter(&end);
	__int64 ms_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000);
	__int64 micro_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000000);
	printf("millisecond : %d, microsecond : %d\n", (int)ms_interval, (int)micro_interval);*/
}

int main() {
	scanf_s("%d", &n); //정수 n
	scanf_s("%d", &m); //스레드 개수 m

	eratosthenes();

	for (int i = 0; i <= n; i++)
		if (isPrime(i))
			printf("%d ", i);
}