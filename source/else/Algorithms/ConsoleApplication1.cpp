// ConsoleApplication1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

//#include "stdafx.h"

#if 0
#if (TEST)
#define TIMER	0.1
#endif

int _tmain(int argc, _TCHAR* argv[])
{

	printf("%f\n", (float)TIMER);

	return 0;
}

#endif

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <process.h>
#include <Winbase.h>
#define MAX 100000000
#define threadMAX 100
using namespace std;

LARGE_INTEGER start, end, f;

int n, m, sqrtn;
unsigned char msieve[MAX / 8];
int sharingI = 2;
int threadPartialIndex[threadMAX];

inline bool isPrime(int k) {
	return msieve[k >> 3] & (1 << (k & 7));
}

inline void setPrime(int k) {
	msieve[k >> 3] &= ~(1 << (k & 7));
}

/*unsigned __stdcall ThreadFunc(void* threadPartialIndex)
{
int i = ++sharingI;
while (i <= sqrtn) {
if (isPrime(i))
for (int j = i * i; j <= n; j += i)
setPrime(j);
i++;
}
_endthreadex(0);
return 0;
}*/

/*unsigned __stdcall ThreadFunc(void* threadParameter)
{
QueryPerformanceCounter(&start);
unsigned char sieve[MAX / 8];
memset(sieve, 255, sizeof(sieve));
sieve[0 >> 3] &= ~(1 << (0 & 7));
sieve[1 >> 3] &= ~(1 << (1 & 7));

int tlp = (int)threadParameter;

for (int i = 1 + (tlp * 2); i <= sqrtn; i += m*2) {
if (sieve[i >> 3] & (1 << (i & 7))) {
for (int j = i * i; j <= n; j += i)
sieve[j >> 3] &= ~(1 << (j & 7));
printf("%d : %d\n", (int)threadParameter, i);
}
}

for (int i = 0; i < threadN / 8; i++) {
msieve[i] &= sieve[i];
}

QueryPerformanceCounter(&end);
__int64 ms_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000);
__int64 micro_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000000);
printf("millisecond : %d, microsecond : %d\n", (int)ms_interval, (int)micro_interval);
_endthreadex(0);
return 0;
}*/

unsigned __stdcall ThreadFunc(void* threadParameter)
{
	QueryPerformanceCounter(&start);

	int &i = sharingI;
	int tlp = (int)threadParameter;

	while (i <= sqrtn) {
		if (msieve[i >> 3] & (1 << (i & 7))) {
			printf("%d\n", i);
			for (int j = i * i; j <= n; j += i)
				msieve[j >> 3] &= ~(1 << (j & 7));
		}
		if (i == 2) i++;
		else i += 2;
	}
	QueryPerformanceCounter(&end);
	__int64 ms_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000);
	__int64 micro_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000000);
	printf("millisecond : %d, microsecond : %d\n", (int)ms_interval, (int)micro_interval);
	_endthreadex(0);
	return 0;
}

void eratosthenes() {
	memset(msieve, 255, sizeof(msieve));
	setPrime(0);
	setPrime(1);

	sqrtn = (int)sqrt((double)n);
	HANDLE hThread[threadMAX];
	unsigned threadID[threadMAX];

	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&start);
	for (int i = 0; i < m; i++) {
		threadPartialIndex[i] = i;
		hThread[i] = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunc, (void*)threadPartialIndex[i], 0, &threadID[i]);
	}

	WaitForMultipleObjects(m, hThread, true, INFINITE);

	for (int i = 0; i < m; i++) {
		CloseHandle(hThread[i]);
	}

	QueryPerformanceCounter(&end);
	__int64 ms_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000);
	__int64 micro_interval = (end.QuadPart - start.QuadPart) / (f.QuadPart / 1000000);
	printf("millisecond : %d, microsecond : %d\n", (int)ms_interval, (int)micro_interval);
}

int main() {
//	scanf_s("%d", &n); //정수 n
//	scanf_s("%d", &m); //스레드 개수 m
	n = 100000;
	m = 90;

	eratosthenes();

	/*for (int i = 0; i <= n; i++)
	if (isPrime(i))
	printf("%d ", i);*/
}