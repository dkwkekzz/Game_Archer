#include <iostream>
#include <algorithm>
using namespace std;
#define BMAX 10000000

int n, m;
int sushi[20][2];

/*int cashe[BMAX + 1];
int budgetCalc(int amount) {
	if (amount <= 0) return 0;

	int &ret = cashe[amount];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < n; i++) {
		if(amount >= sushi[i][0])
			ret = max(ret, budgetCalc(amount - sushi[i][0]) + sushi[i][1]);
	}
	
	return ret;
	
}*/

int C[201];
int budgetCalc2() {
	int ret = 0;
	C[0] = 0;
	for (int i = 1; i <= m; i++) {
		int cand = 0;
		for (int dish = 0; dish < n; dish++) {
			if(i >= sushi[dish][0])
				cand = max(cand, C[(i - sushi[dish][0]) % 201] + sushi[dish][1]);
		}
		C[i % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}

int main() {
	//memset(cashe, -1, sizeof(cashe));
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> sushi[i][0] >> sushi[i][1];
		sushi[i][0] /= 100;
	}
	m /= 100;
	cout << budgetCalc2() << endl;

}