#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 10005, MOD = 1000000007;
int n, altar[MAXN], C[MAXN][2];

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	cin.sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> altar[i];
	C[0][0] = altar[0] <= 0 ? 1 : 0;
	for (int i = 1; i < n; i++)
	for (int h = 0; h <= min(i, n - i); h++){
		C[h][i % 2] = ((C[h + 1][(i - 1) % 2] + C[h][(i - 1) % 2]) % MOD + C[h - 1][(i - 1) % 2]) % MOD;
		if (altar[i] >= 0 && h != altar[i]) C[h][i % 2] = 0;
	}
	cout << C[0][(n - 1) % 2] << endl;

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}