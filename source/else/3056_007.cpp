#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <cmath>
using namespace std;
typedef long long int64;
const int MAX_N = 20;
int n;
vector<int> missions[MAX_N][MAX_N];
vector<int> cache[1 << MAX_N];

double cache1[1 << MAX_N];
double missions1[MAX_N][MAX_N];

void normalize(vector<int>& a){
	int n = a.size();
	a.push_back(0);

	for (int i = 0; i < n; i++){
		//해당 숫자가 음수라면
		if (a[i] < 0){
			//만일 -11을 처리한다면, 음수를 모두 없앤다음(9를 더해야 모든 수를 올릴 수 있고 0때문에 10보다는 작아야 한다.)
			//-11 + 20으로 계산한다.
			int borrow = (abs(a[i]) + 9) / 10;
			//20을 빌려준다.
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else{
			a[i + 1] += a[i] / 10;
			a[i] %= 10;
		}
	}
	while (a.size() > 1 && a.back() == 0) a.pop_back();
}

//multiply({3, 2, 1}, {6, 5, 4}) = 123 * 456
vector<int> multiply(const vector<int>& a, const vector<int>& b){
	vector<int> c(a.size() + b.size() + 1, 0);

	for (int i = 0; i < a.size(); i++){
		for (int j = 0; j < b.size(); j++){
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);

	return c;
}

vector<int> convertNumber(int a){
	vector<int> ret;
	while (a > 0){
		int q = a % 10;
		ret.push_back(q);
		a /= 10;
	}
	return ret;
}

double scaffolding(int state, int order){
	if (order == n) return 1;

	double &ret = cache1[state];
	if (ret > -0.5) return ret;

	ret = 0;
	for (int choice = 0; choice < n; choice++){
		if ((state & (1 << choice)) == 0){
			ret = max(ret, (missions1[order][choice] / 100.0)
				* scaffolding((state | (1 << choice)), order + 1));
		}
	}
	return ret;
}

bool operator<(const vector<int> &a, const vector<int> &b){
	if(a.size() == b.size()){
		for (int i = a.size()-1; i >= 0; i--){
			if (a[i] == b[i]) continue;
			else return a[i] < b[i];
		}
	}
	else return a.size() < b.size();
	return false;
}

vector<int> setMissions(int state, int order){
	if (order == n) return vector<int>(1, 1);
	
	vector<int> &ret = cache[state];
	if (ret.size() > 0) return ret;

	ret = vector<int>(1, 1);
	for (int choice = 0; choice < n; choice++){
		if (!(state & (1 << choice))){
			vector<int> cand = setMissions(state | (1 << choice), order + 1);
			cand = multiply(cand, missions[order][choice]);
			if (ret < cand) ret = cand;
		}
	}
	return ret;
}

int main(int argc, char** argv) {
	FILE* stream;
	freopen_s(&stream, "input.txt", "r", stdin);

	memset(cache1, -1, sizeof(cache1));
	scanf_s("%d", &n);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {
		int a; scanf_s("%d", &a);
		missions1[i][j] = static_cast<double>(a);
		missions[i][j] = convertNumber(a);
	}
	double ret = 0, part = 1;
	vector<int> temp = setMissions(0, 0);
	for (int i = 0; i < temp.size(); i++){
		ret += part*temp[i];
		part *= 10;
	}
	printf("%.6lf\n", ret / pow(10, 2*n-2));
	printf("%.6lf\n", scaffolding(0, 0)*100.0);

	return 0;	// 정상종료 시 반드시 0을 리턴해야 합니다.
}